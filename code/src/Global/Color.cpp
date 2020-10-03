#include "Color.h"

#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QStandardPaths>

Theme::Theme(const QString &themePath)
{
    generateDefaultTheme();
    QFile theme(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+themePath);
    if(theme.open(QIODevice::ReadOnly))
    {
        useDefault = false;
        QJsonDocument doc = QJsonDocument::fromJson(theme.readAll());
        customTheme = doc.toVariant().toMap();
        qDebug() << "Using custom colors.";
        theme.close();
        return;
    }
    qDebug() << "Using default colors.";
}
QColor Theme::get( const QString &colorName )
{
    if(useDefault)
    {
        return QColor("#"+defaultTheme[colorName].toString());
    }
    else
    {
        if(customTheme.contains(colorName))
            return QColor("#"+customTheme[colorName].toString());
        else
            return QColor("#"+defaultTheme[colorName].toString());
    }

}
QString Theme::getString( const QString &colorName )
{
    if(useDefault)
    {
        return "#"+defaultTheme[colorName].toString();
    }
    else
    {
        if(customTheme.contains(colorName))
            return "#"+customTheme[colorName].toString();
        else
            return "#"+defaultTheme[colorName].toString();
    }

}
void Theme::generateDefaultTheme()
{
    defaultTheme["QLabelText"]                              = "666666";
    defaultTheme["MainWindowBackground"]                    = "F0F2F5";
    defaultTheme["MainWindowTopBarBackground"]              = "FFFFFF";
    defaultTheme["MainWindowTopBarBorderBottom"]            = "EEEEEE";
    defaultTheme["MenuBackground"]                          = "FFFFFF";
    defaultTheme["MenuBorder"]                              = "EEEEEE";

    defaultTheme["ToggleButtonDefaultActiveBackground"]     = "AAAAAA";
    defaultTheme["ToggleButtonDefaultInactiveBackground"]   = "EEEEEE";
    defaultTheme["ToggleButtonDefaultActiveIcon"]           = "333333";
    defaultTheme["ToggleButtonDefaultInactiveIcon"]         = "666666";
    defaultTheme["PlaybackButtonActiveIcon"]                = "FFFFFF";
    defaultTheme["PlaybackButtonInactiveIcon"]              = "666666";
    defaultTheme["PlaybackButtonActiveBackground"]          = "42B72A";
    defaultTheme["PlaybackButtonInactiveBackground"]        = "EEEEEE";

    defaultTheme["RecordButtonActiveIcon"]                  = "FFFFFF";
    defaultTheme["RecordButtonInactiveIcon"]                = "C83028";
    defaultTheme["RecordButtonActiveBackground"]            = "C83028";
    defaultTheme["RecordButtonInactiveBackground"]          = "EEEEEE";

    defaultTheme["AutomationButtonActiveIcon"]              = "FFFFFF";
    defaultTheme["AutomationButtonInactiveIcon"]            = "666666";
    defaultTheme["AutomationButtonActiveBackground"]        = "2477F2";
    defaultTheme["AutomationButtonInactiveBackground"]      = "EEEEEE";

    defaultTheme["ListItemDefaultInactiveBackground"]       = "FFFFFF";
    defaultTheme["ListItemDefaultActiveBackground"]         = "2477F2";
    defaultTheme["ListItemDefaultInactiveContent"]          = "666666";
    defaultTheme["ListItemDefaultActiveContent"]            = "FFFFFF";

}


Theme Color::theme = Theme("/Levels/themes/custom.color");
