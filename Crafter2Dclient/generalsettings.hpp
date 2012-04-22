#ifndef GENERALSETTINGS_HPP
#define GENERALSETTINGS_HPP

#include <Utils/Singleton>

#include <QSettings>

class GeneralSettings : Utils::Singleton<GeneralSettings>
{
    friend class Utils::Singleton<GeneralSettings>;

public:
    static double distanceToRefreshNearbyObject();

private:
    GeneralSettings();

    QSettings m_settings;
};

#endif // GENERALSETTINGS_HPP
