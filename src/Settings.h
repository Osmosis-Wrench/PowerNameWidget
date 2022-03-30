#pragma once

class Settings
{
public:
	[[nodiscard]] static Settings* GetSingleton()
	{
		static Settings singleton;
		return std::addressof(singleton);
	}

	void Load()
	{
		constexpr auto path = L"Data/SKSE/Plugins/osmo_powerNameWidget.ini";

		CSimpleIniA ini;
		ini.SetUnicode();

		ini.LoadFile(path);

		detail::get_value(ini, widget_showPowers, "Widget", "Show Powers", ";Whether or not to show the name of currently selected power, default is true");
		detail::get_value(ini, widget_showShouts, "Widget", "Show Shouts", ";Whether or not to show the name of currently selected shout, default is true");
		detail::get_value(ini, widget_xpos, "Widget", "Widget X Position", ";The X Position for the widget, default is 80.000000");
		detail::get_value(ini, widget_ypos, "Widget", "Widget Y Position", ";The Y Position for the widget, default is 170.000000");
		detail::get_value(ini, widget_rotation, "Widget", "Widget Rotation", ";The rotation for the widget, default is 0.000000");
		detail::get_value(ini, widget_xscale, "Widget", "Widget X scale", ";The X scale of the widget, default is 100.000000");
		detail::get_value(ini, widget_yscale, "Widget", "Widget Y scale", ";The Y scale of the widget, default is 100.000000");
		detail::get_value(ini, text_xpos, "Widget", "Text X Position modifier", ";The X Position modifier for the text to allow for better aligning custom fonts, default is 0.000000");
		detail::get_value(ini, text_ypos, "Widget", "Text Y Position modifier", ";The Y Position modifier for the text to allow for better aligning custom fonts, default is 0.000000");

		ini.SaveFile(path);
	}

	bool widget_showPowers = true;
	bool widget_showShouts = true;
	float widget_xpos{ 80.0f };
	float widget_ypos{ 170.0f };
	float widget_rotation{ 0.0f };
	float widget_xscale{ 100.0f };
	float widget_yscale{ 100.0f };
	float text_xpos{ 0.0f };
	float text_ypos{ 0.0f };

private:
	struct detail
	{
		static void get_value(CSimpleIniA& a_ini, std::uint32_t& a_value, const char* a_section, const char* a_key, const char* a_comment)
		{
			try {
				a_value = string::lexical_cast<std::uint32_t>(a_ini.GetValue(a_section, a_key, "0"));
				a_ini.SetValue(a_section, a_key, std::to_string(a_value).c_str(), a_comment);
			} catch (...) {
			}
		}

		static void get_value(CSimpleIniA& a_ini, float& a_value, const char* a_section, const char* a_key, const char* a_comment)
		{
			a_value = static_cast<float>(a_ini.GetDoubleValue(a_section, a_key, a_value));
			a_ini.SetDoubleValue(a_section, a_key, a_value, a_comment);
		}

		static void get_value(CSimpleIniA& a_ini, bool& a_value, const char* a_section, const char* a_key, const char* a_comment)
		{
			a_value = a_ini.GetBoolValue(a_section, a_key, a_value);
			a_ini.SetBoolValue(a_section, a_key, a_value, a_comment);
		};

		static void get_value(CSimpleIniA& a_ini, std::string& a_value, const char* a_section, const char* a_key, const char* a_comment)
		{
			a_value = a_ini.GetValue(a_section, a_key, a_value.c_str());
			a_ini.SetValue(a_section, a_key, a_value.c_str(), a_comment);
		};
	};
};
