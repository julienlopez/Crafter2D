#include "generalsettings.hpp"

GeneralSettings::GeneralSettings(): m_settings("general_settings.ini", QSettings::IniFormat)
{
}

double GeneralSettings::distanceToRefreshNearbyObject()
{
    return instance().m_settings.value("distanceToRefreshNearbyObjects", 50).toDouble();
}
