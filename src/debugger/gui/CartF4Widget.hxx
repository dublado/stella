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
// Copyright (c) 1995-2019 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef CARTRIDGEF4_WIDGET_HXX
#define CARTRIDGEF4_WIDGET_HXX

class CartridgeF4;
class PopUpWidget;

#include "CartDebugWidget.hxx"

class CartridgeF4Widget : public CartDebugWidget
{
  public:
    CartridgeF4Widget(GuiObject* boss, const GUI::Font& lfont,
                      const GUI::Font& nfont,
                      int x, int y, int w, int h,
                      CartridgeF4& cart);
    virtual ~CartridgeF4Widget() = default;

  private:
    CartridgeF4& myCart;
    PopUpWidget* myBank;

    enum { kBankChanged = 'bkCH' };

  private:
    void loadConfig() override;
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;

    string bankState() override;

    // Following constructors and assignment operators not supported
    CartridgeF4Widget() = delete;
    CartridgeF4Widget(const CartridgeF4Widget&) = delete;
    CartridgeF4Widget(CartridgeF4Widget&&) = delete;
    CartridgeF4Widget& operator=(const CartridgeF4Widget&) = delete;
    CartridgeF4Widget& operator=(CartridgeF4Widget&&) = delete;
};

#endif
