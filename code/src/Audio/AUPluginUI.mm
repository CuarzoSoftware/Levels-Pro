#include <Audio/AUPluginUI.h>
#import <Foundation/NSURL.h>
#import <Foundation/NSString.h>
#import <AppKit/AppKit.h>

/*!
    \class AudioUnitWrap
    \brief The AudioUnitWrap class...

    \inheaderfile Audio/AudioUnitWrap.h
    \ingroup Audio
    \inmodule Audio

    \inherits QObject
*/

@interface NotificationObject: NSObject
{
    AudioUnitWrap *_auWrap;

}

-(NotificationObject*) withView:(AudioUnitWrap *)auWrap;
-(void) auViewResized:(NSNotification *)notification;
-(void) windowWillStartLiveResizeHandler:(NSNotification *)notification;
-(void) windowWillEndLiveResizeHandler:(NSNotification *)notification;
@end
@implementation NotificationObject

- (NotificationObject*)withView:(AudioUnitWrap *)auWrap
{
   _auWrap = auWrap;
   return self;
}

- (void)auViewResized:(NSNotification *)notification
{
    (void) notification;
    if(_auWrap->in_live_resize) return;

    NSUInteger old_auto_resize = [_auWrap->view autoresizingMask];
    CGRect newFrame = [_auWrap->view frame];
    [_auWrap->view setAutoresizingMask:NSViewNotSizable];
    _auWrap->childWidget->resize(newFrame.size.width,newFrame.size.height);
    _auWrap->topWidget->setFixedSize(newFrame.size.width,newFrame.size.height);
    [_auWrap->view setFrame:newFrame];
    [_auWrap->view setAutoresizingMask:old_auto_resize];

}

-(void) windowWillStartLiveResizeHandler:(NSNotification *)notification
{
    (void) notification;
    qDebug() << "Resizing";
    _auWrap->in_live_resize = true;
}
-(void) windowWillEndLiveResizeHandler:(NSNotification *)notification
{
    (void) notification;
    _auWrap->in_live_resize = false;
    qDebug() << "Not Resizing";
}


@end

void opengl(NSView *v)
{
    NSArray <NSView*> *arr = [v subviews];
    for(int i = 0;i<arr.count;i++)
    {
        [arr[i] setWantsBestResolutionOpenGLSurface:NO];
    }
}

void cocoa_view_resized (QMacCocoaViewContainer *au_view)
{
    NSRect new_frame = [au_view->cocoaView() frame];
    NSUInteger old_auto_resize = [au_view->cocoaView() autoresizingMask];
    [au_view->cocoaView() setFrame:new_frame];
    [au_view->cocoaView() setAutoresizingMask:NSViewNotSizable];
    [au_view->cocoaView() setAutoresizingMask:old_auto_resize];

    au_view->setFixedSize(new_frame.size.width,new_frame.size.height);

}
AudioUnitWrap::AudioUnitWrap()
{

}

void AudioUnitWrap::getAudioUnit(void *un)
{
    AudioUnit unit = (AudioUnit)un;
    UInt32 dataSize;
    Boolean isWritable;
    AudioUnitCocoaViewInfo * cocoaViewInfo = NULL;
    UInt32 numberOfClasses;
    NSSize size = QSize(800,800).toCGSize();


    OSStatus result = AudioUnitGetPropertyInfo(unit, kAudioUnitProperty_CocoaUI, kAudioUnitScope_Global, 0, &dataSize, &isWritable);

    numberOfClasses = (dataSize - sizeof(CFURLRef)) / sizeof(CFStringRef);

    NSURL * CocoaViewBundlePath = nil;
    NSString * factoryClassName = nil;

    if((result == noErr) && (numberOfClasses > 0)) {
        cocoaViewInfo = (AudioUnitCocoaViewInfo *)malloc(dataSize);
        if(AudioUnitGetProperty(unit,
                                kAudioUnitProperty_CocoaUI,
                                kAudioUnitScope_Global,
                                0,
                                cocoaViewInfo,
                                &dataSize) == noErr) {
            CocoaViewBundlePath	= (NSURL *)cocoaViewInfo->mCocoaAUViewBundleLocation;
            factoryClassName = (NSString *)cocoaViewInfo->mCocoaAUViewClass[0];
        }
        else {
            if(cocoaViewInfo != NULL) {
                free(cocoaViewInfo);
                cocoaViewInfo = NULL;
            }
        }
    }

    NSView * unitView = nil;

    if(CocoaViewBundlePath && factoryClassName) {
        NSBundle * viewBundle = [NSBundle bundleWithPath:[CocoaViewBundlePath path]];
        if(viewBundle == nil) {
            NSLog(@"Error loading AU view's bundle");
            return;
        }

        Class factoryClass = [viewBundle classNamed:factoryClassName];
        if(factoryClass == Nil) {
            NSLog(@"Error getting AU view's factory class from bundle");
            return;
        }

        id factoryInstance = [[factoryClass alloc] init];
        unitView = [factoryInstance uiViewForAudioUnit:unit withSize:size];
        qDebug() << size.width << " ------ " << size.height;
        [CocoaViewBundlePath release];
        [factoryInstance release];

        if(cocoaViewInfo) {
            UInt32 i;
            for(i = 0; i < numberOfClasses; i++)
                CFRelease(cocoaViewInfo->mCocoaAUViewClass[i]);

            free(cocoaViewInfo);
        }
    }
    opengl(unitView);
    topWidget->setStyleSheet("background-color: green");
    childWidget->setStyleSheet("background-color: red");
    view = unitView;


    NSWindow *win = (NSWindow*) topWidget->winId();
    [(NSView*)childWidget->winId() addSubview:unitView];
    NSRect  frame = [unitView frame];
    req_width  = frame.size.width;
    req_height = frame.size.height;


    childWidget->resize(req_width,req_height);
    topWidget->setFixedSize(req_width,req_height);




    resizable  = [unitView autoresizingMask];

    qDebug() << "Is Rezi: " << resizable;




    NotificationObject *_notify = [[NotificationObject alloc] withView:this];
    [[NSNotificationCenter defaultCenter]
    addObserver:_notify
    selector:@selector(auViewResized:) name:NSViewFrameDidChangeNotification
    object:unitView];

    [[NSNotificationCenter defaultCenter]
    addObserver:_notify
    selector:@selector(windowWillStartLiveResizeHandler:) name:NSWindowWillStartLiveResizeNotification
    object:win];

    [[NSNotificationCenter defaultCenter]
    addObserver:_notify
    selector:@selector(windowWillEndLiveResizeHandler:) name:NSWindowDidEndLiveResizeNotification
    object:win];

    topWidget->show();
   // [win makeKeyAndOrderFront:NSApp];

    /*
    [[NSNotificationCenter defaultCenter] addObserver:_resize_notify
            selector:@selector(windowWillStartLiveResizeHandler:) name:NSWindowWillStartLiveResizeNotification
            object:win];

        [[NSNotificationCenter defaultCenter] addObserver:_resize_notify
            selector:@selector(windowWillEndLiveResizeHandler:) name:NSWindowDidEndLiveResizeNotification
            object:win];
    */
    //viewCont->show();


    /*
    NSRect frame = NSMakeRect(0, 0, 200, 200);
    NSWindow* window  = [[[NSWindow alloc] initWithContentRect:frame
                        styleMask:NSWindowStyleMaskTitled
                        backing:NSBackingStoreBuffered
                        defer:NO] autorelease];

    [window setBackgroundColor:[NSColor blueColor]];
    [window makeKeyAndOrderFront:NSApp];
    [window setContentView:unitView];

    [window makeKeyAndOrderFront:NSApp];
    */

    //NotificationObject *_notify = [[NotificationObject alloc] withView:unitView withWindow:window];


}
