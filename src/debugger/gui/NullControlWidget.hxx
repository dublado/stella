//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2018 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef NULLCONTROL_WIDGET_HXX
#define NULLCONTROL_WIDGET_HXX

class GuiObject;

#include "ControllerWidget.hxx"

class NullControlWidget : public ControllerWidget
{
  public:
    NullControlWidget(GuiObject* boss, const GUI::Font& font, int x, int y,
                      Controller& controller)
      : ControllerWidget(boss, font, x, y, controller)
    {
      ostringstream buf;
      buf << getHeader();
      const int fontHeight = font.getFontHeight(),
                lineHeight = font.getLineHeight(),
                lwidth = std::max(font.getStringWidth(buf.str()),
                font.getStringWidth("Controller input"));
      new StaticTextWidget(boss, font, x, y+2, lwidth,
                           fontHeight, buf.str(), TextAlign::Left);
      new StaticTextWidget(boss, font, x, y+2+2*lineHeight, lwidth,
                           fontHeight, "Controller input", TextAlign::Center);
      new StaticTextWidget(boss, font, x, y+2+3*lineHeight, lwidth,
                           fontHeight, "not available",
                           TextAlign::Center);
    }

    virtual ~NullControlWidget() = default;

  private:
    // Following constructors and assignment operators not supported
    NullControlWidget() = delete;
    NullControlWidget(const NullControlWidget&) = delete;
    NullControlWidget(NullControlWidget&&) = delete;
    NullControlWidget& operator=(const NullControlWidget&) = delete;
    NullControlWidget& operator=(NullControlWidget&&) = delete;
};

#endif
