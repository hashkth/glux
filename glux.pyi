
from typing import overload, Tuple, Callable, List, Optional


class imgui:

    # ==================================================================
    # Flags & Enumerations
    # ==================================================================

    # ------------------------------------------------------------------
    # WindowFlags  (bitmask)
    # ------------------------------------------------------------------
    class WindowFlags:
        None_:                      imgui.WindowFlags
        NoTitleBar:                 imgui.WindowFlags
        NoResize:                   imgui.WindowFlags
        NoMove:                     imgui.WindowFlags
        NoScrollbar:                imgui.WindowFlags
        NoScrollWithMouse:          imgui.WindowFlags
        NoCollapse:                 imgui.WindowFlags
        AlwaysAutoResize:           imgui.WindowFlags
        NoBackground:               imgui.WindowFlags
        NoSavedSettings:            imgui.WindowFlags
        NoMouseInputs:              imgui.WindowFlags
        MenuBar:                    imgui.WindowFlags
        HorizontalScrollbar:        imgui.WindowFlags
        NoFocusOnAppearing:         imgui.WindowFlags
        NoBringToFrontOnFocus:      imgui.WindowFlags
        AlwaysVerticalScrollbar:    imgui.WindowFlags
        AlwaysHorizontalScrollbar:  imgui.WindowFlags
        NoNavInputs:                imgui.WindowFlags
        NoNavFocus:                 imgui.WindowFlags
        UnsavedDocument:            imgui.WindowFlags
        NoNav:                      imgui.WindowFlags  # NoNavInputs | NoNavFocus
        NoDecoration:               imgui.WindowFlags  # NoTitleBar | NoResize | NoScrollbar | NoCollapse
        NoInputs:                   imgui.WindowFlags  # NoMouseInputs | NoNavInputs | NoNavFocus
        def __or__(self, other: imgui.WindowFlags) -> imgui.WindowFlags: ...
        def __and__(self, other: imgui.WindowFlags) -> imgui.WindowFlags: ...
        def __xor__(self, other: imgui.WindowFlags) -> imgui.WindowFlags: ...
        def __invert__(self) -> imgui.WindowFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # ChildFlags  (bitmask)
    # ------------------------------------------------------------------
    class ChildFlags:
        None_:                  imgui.ChildFlags
        Borders:                imgui.ChildFlags
        AlwaysUseWindowPadding: imgui.ChildFlags
        ResizeX:                imgui.ChildFlags
        ResizeY:                imgui.ChildFlags
        AutoResizeX:            imgui.ChildFlags
        AutoResizeY:            imgui.ChildFlags
        AlwaysAutoResize:       imgui.ChildFlags
        FrameStyle:             imgui.ChildFlags
        def __or__(self, other: imgui.ChildFlags) -> imgui.ChildFlags: ...
        def __and__(self, other: imgui.ChildFlags) -> imgui.ChildFlags: ...
        def __xor__(self, other: imgui.ChildFlags) -> imgui.ChildFlags: ...
        def __invert__(self) -> imgui.ChildFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # ItemFlags  (bitmask)
    # ------------------------------------------------------------------
    class ItemFlags:
        None_:              imgui.ItemFlags
        NoTabStop:          imgui.ItemFlags
        NoNav:              imgui.ItemFlags
        NoNavDefaultFocus:  imgui.ItemFlags
        ButtonRepeat:       imgui.ItemFlags
        AutoClosePopups:    imgui.ItemFlags
        AllowDuplicateId:   imgui.ItemFlags
        def __or__(self, other: imgui.ItemFlags) -> imgui.ItemFlags: ...
        def __and__(self, other: imgui.ItemFlags) -> imgui.ItemFlags: ...
        def __xor__(self, other: imgui.ItemFlags) -> imgui.ItemFlags: ...
        def __invert__(self) -> imgui.ItemFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # InputTextFlags  (bitmask)
    # ------------------------------------------------------------------
    class InputTextFlags:
        None_:                  imgui.InputTextFlags
        CharsDecimal:           imgui.InputTextFlags
        CharsHexadecimal:       imgui.InputTextFlags
        CharsScientific:        imgui.InputTextFlags
        CharsUppercase:         imgui.InputTextFlags
        CharsNoBlank:           imgui.InputTextFlags
        AllowTabInput:          imgui.InputTextFlags
        EnterReturnsTrue:       imgui.InputTextFlags
        EscapeClearsAll:        imgui.InputTextFlags
        CtrlEnterForNewLine:    imgui.InputTextFlags
        ReadOnly:               imgui.InputTextFlags
        Password:               imgui.InputTextFlags
        AlwaysOverwrite:        imgui.InputTextFlags
        AutoSelectAll:          imgui.InputTextFlags
        ParseEmptyRefVal:       imgui.InputTextFlags
        DisplayEmptyRefVal:     imgui.InputTextFlags
        NoHorizontalScroll:     imgui.InputTextFlags
        NoUndoRedo:             imgui.InputTextFlags
        ElideLeft:              imgui.InputTextFlags
        CallbackCompletion:     imgui.InputTextFlags
        CallbackHistory:        imgui.InputTextFlags
        CallbackAlways:         imgui.InputTextFlags
        CallbackCharFilter:     imgui.InputTextFlags
        CallbackResize:         imgui.InputTextFlags
        CallbackEdit:           imgui.InputTextFlags
        def __or__(self, other: imgui.InputTextFlags) -> imgui.InputTextFlags: ...
        def __and__(self, other: imgui.InputTextFlags) -> imgui.InputTextFlags: ...
        def __xor__(self, other: imgui.InputTextFlags) -> imgui.InputTextFlags: ...
        def __invert__(self) -> imgui.InputTextFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TreeNodeFlags  (bitmask)
    # ------------------------------------------------------------------
    class TreeNodeFlags:
        None_:                  imgui.TreeNodeFlags
        Selected:               imgui.TreeNodeFlags
        Framed:                 imgui.TreeNodeFlags
        AllowOverlap:           imgui.TreeNodeFlags
        NoTreePushOnOpen:       imgui.TreeNodeFlags
        NoAutoOpenOnLog:        imgui.TreeNodeFlags
        DefaultOpen:            imgui.TreeNodeFlags
        OpenOnDoubleClick:      imgui.TreeNodeFlags
        OpenOnArrow:            imgui.TreeNodeFlags
        Leaf:                   imgui.TreeNodeFlags
        Bullet:                 imgui.TreeNodeFlags
        FramePadding:           imgui.TreeNodeFlags
        SpanAvailWidth:         imgui.TreeNodeFlags
        SpanFullWidth:          imgui.TreeNodeFlags
        SpanLabelWidth:         imgui.TreeNodeFlags
        SpanAllColumns:         imgui.TreeNodeFlags
        LabelSpanAllColumns:    imgui.TreeNodeFlags
        NavLeftJumpsToParent:   imgui.TreeNodeFlags
        CollapsingHeader:       imgui.TreeNodeFlags  # Framed | NoTreePushOnOpen | NoAutoOpenOnLog
        def __or__(self, other: imgui.TreeNodeFlags) -> imgui.TreeNodeFlags: ...
        def __and__(self, other: imgui.TreeNodeFlags) -> imgui.TreeNodeFlags: ...
        def __xor__(self, other: imgui.TreeNodeFlags) -> imgui.TreeNodeFlags: ...
        def __invert__(self) -> imgui.TreeNodeFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # PopupFlags  (bitmask)
    # ------------------------------------------------------------------
    class PopupFlags:
        None_:                      imgui.PopupFlags
        MouseButtonLeft:            imgui.PopupFlags
        MouseButtonRight:           imgui.PopupFlags
        MouseButtonMiddle:          imgui.PopupFlags
        MouseButtonMask_:           imgui.PopupFlags
        MouseButtonDefault_:        imgui.PopupFlags
        NoReopen:                   imgui.PopupFlags
        NoOpenOverExistingPopup:    imgui.PopupFlags
        NoOpenOverItems:            imgui.PopupFlags
        AnyPopupId:                 imgui.PopupFlags
        AnyPopupLevel:              imgui.PopupFlags
        AnyPopup:                   imgui.PopupFlags  # AnyPopupId | AnyPopupLevel
        def __or__(self, other: imgui.PopupFlags) -> imgui.PopupFlags: ...
        def __and__(self, other: imgui.PopupFlags) -> imgui.PopupFlags: ...
        def __xor__(self, other: imgui.PopupFlags) -> imgui.PopupFlags: ...
        def __invert__(self) -> imgui.PopupFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # SelectableFlags  (bitmask)
    # ------------------------------------------------------------------
    class SelectableFlags:
        None_:              imgui.SelectableFlags
        NoAutoClosePopups:  imgui.SelectableFlags
        SpanAllColumns:     imgui.SelectableFlags
        AllowDoubleClick:   imgui.SelectableFlags
        Disabled:           imgui.SelectableFlags
        AllowOverlap:       imgui.SelectableFlags
        Highlight:          imgui.SelectableFlags
        def __or__(self, other: imgui.SelectableFlags) -> imgui.SelectableFlags: ...
        def __and__(self, other: imgui.SelectableFlags) -> imgui.SelectableFlags: ...
        def __xor__(self, other: imgui.SelectableFlags) -> imgui.SelectableFlags: ...
        def __invert__(self) -> imgui.SelectableFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # ComboFlags  (bitmask)
    # ------------------------------------------------------------------
    class ComboFlags:
        None_:           imgui.ComboFlags
        PopupAlignLeft:  imgui.ComboFlags
        HeightSmall:     imgui.ComboFlags
        HeightRegular:   imgui.ComboFlags
        HeightLarge:     imgui.ComboFlags
        HeightLargest:   imgui.ComboFlags
        NoArrowButton:   imgui.ComboFlags
        NoPreview:       imgui.ComboFlags
        WidthFitPreview: imgui.ComboFlags
        HeightMask_:     imgui.ComboFlags
        def __or__(self, other: imgui.ComboFlags) -> imgui.ComboFlags: ...
        def __and__(self, other: imgui.ComboFlags) -> imgui.ComboFlags: ...
        def __xor__(self, other: imgui.ComboFlags) -> imgui.ComboFlags: ...
        def __invert__(self) -> imgui.ComboFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TabBarFlags  (bitmask)
    # ------------------------------------------------------------------
    class TabBarFlags:
        None_:                          imgui.TabBarFlags
        Reorderable:                    imgui.TabBarFlags
        AutoSelectNewTabs:              imgui.TabBarFlags
        TabListPopupButton:             imgui.TabBarFlags
        NoCloseWithMiddleMouseButton:   imgui.TabBarFlags
        NoTabListScrollingButtons:      imgui.TabBarFlags
        NoTooltip:                      imgui.TabBarFlags
        DrawSelectedOverline:           imgui.TabBarFlags
        FittingPolicyResizeDown:        imgui.TabBarFlags
        FittingPolicyScroll:            imgui.TabBarFlags
        FittingPolicyMask_:             imgui.TabBarFlags
        FittingPolicyDefault_:          imgui.TabBarFlags
        def __or__(self, other: imgui.TabBarFlags) -> imgui.TabBarFlags: ...
        def __and__(self, other: imgui.TabBarFlags) -> imgui.TabBarFlags: ...
        def __xor__(self, other: imgui.TabBarFlags) -> imgui.TabBarFlags: ...
        def __invert__(self) -> imgui.TabBarFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TabItemFlags  (bitmask)
    # ------------------------------------------------------------------
    class TabItemFlags:
        None_:                          imgui.TabItemFlags
        UnsavedDocument:                imgui.TabItemFlags
        SetSelected:                    imgui.TabItemFlags
        NoCloseWithMiddleMouseButton:   imgui.TabItemFlags
        NoPushId:                       imgui.TabItemFlags
        NoTooltip:                      imgui.TabItemFlags
        NoReorder:                      imgui.TabItemFlags
        Leading:                        imgui.TabItemFlags
        Trailing:                       imgui.TabItemFlags
        NoAssumedClosure:               imgui.TabItemFlags
        def __or__(self, other: imgui.TabItemFlags) -> imgui.TabItemFlags: ...
        def __and__(self, other: imgui.TabItemFlags) -> imgui.TabItemFlags: ...
        def __xor__(self, other: imgui.TabItemFlags) -> imgui.TabItemFlags: ...
        def __invert__(self) -> imgui.TabItemFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # FocusedFlags  (bitmask)
    # ------------------------------------------------------------------
    class FocusedFlags:
        None_:               imgui.FocusedFlags
        ChildWindows:        imgui.FocusedFlags
        RootWindow:          imgui.FocusedFlags
        AnyWindow:           imgui.FocusedFlags
        NoPopupHierarchy:    imgui.FocusedFlags
        RootAndChildWindows: imgui.FocusedFlags  # RootWindow | ChildWindows
        def __or__(self, other: imgui.FocusedFlags) -> imgui.FocusedFlags: ...
        def __and__(self, other: imgui.FocusedFlags) -> imgui.FocusedFlags: ...
        def __xor__(self, other: imgui.FocusedFlags) -> imgui.FocusedFlags: ...
        def __invert__(self) -> imgui.FocusedFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # HoveredFlags  (bitmask)
    # ------------------------------------------------------------------
    class HoveredFlags:
        None_:                          imgui.HoveredFlags
        ChildWindows:                   imgui.HoveredFlags
        RootWindow:                     imgui.HoveredFlags
        AnyWindow:                      imgui.HoveredFlags
        NoPopupHierarchy:               imgui.HoveredFlags
        AllowWhenBlockedByPopup:        imgui.HoveredFlags
        AllowWhenBlockedByActiveItem:   imgui.HoveredFlags
        AllowWhenOverlappedByItem:      imgui.HoveredFlags
        AllowWhenOverlappedByWindow:    imgui.HoveredFlags
        AllowWhenDisabled:              imgui.HoveredFlags
        NoNavOverride:                  imgui.HoveredFlags
        AllowWhenOverlapped:            imgui.HoveredFlags  # ByItem | ByWindow
        RectOnly:                       imgui.HoveredFlags  # BlockedByPopup | BlockedByActiveItem | OverlappedByItem
        RootAndChildWindows:            imgui.HoveredFlags  # RootWindow | ChildWindows
        ForTooltip:                     imgui.HoveredFlags
        Stationary:                     imgui.HoveredFlags
        DelayNone:                      imgui.HoveredFlags
        DelayShort:                     imgui.HoveredFlags
        DelayNormal:                    imgui.HoveredFlags
        NoSharedDelay:                  imgui.HoveredFlags
        def __or__(self, other: imgui.HoveredFlags) -> imgui.HoveredFlags: ...
        def __and__(self, other: imgui.HoveredFlags) -> imgui.HoveredFlags: ...
        def __xor__(self, other: imgui.HoveredFlags) -> imgui.HoveredFlags: ...
        def __invert__(self) -> imgui.HoveredFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # DragDropFlags  (bitmask)
    # ------------------------------------------------------------------
    class DragDropFlags:
        None_:                      imgui.DragDropFlags
        SourceNoPreviewTooltip:     imgui.DragDropFlags
        SourceNoDisableHover:       imgui.DragDropFlags
        SourceNoHoldToOpenOthers:   imgui.DragDropFlags
        SourceAllowNullID:          imgui.DragDropFlags
        SourceExtern:               imgui.DragDropFlags
        PayloadAutoExpire:          imgui.DragDropFlags
        PayloadNoCrossContext:      imgui.DragDropFlags
        PayloadNoCrossProcess:      imgui.DragDropFlags
        AcceptBeforeDelivery:       imgui.DragDropFlags
        AcceptNoDrawDefaultRect:    imgui.DragDropFlags
        AcceptNoPreviewTooltip:     imgui.DragDropFlags
        AcceptPeekOnly:             imgui.DragDropFlags  # AcceptBeforeDelivery | AcceptNoDrawDefaultRect
        def __or__(self, other: imgui.DragDropFlags) -> imgui.DragDropFlags: ...
        def __and__(self, other: imgui.DragDropFlags) -> imgui.DragDropFlags: ...
        def __xor__(self, other: imgui.DragDropFlags) -> imgui.DragDropFlags: ...
        def __invert__(self) -> imgui.DragDropFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # DataType  (plain enum — no bitwise ops)
    # ------------------------------------------------------------------
    class DataType:
        S8:     imgui.DataType
        U8:     imgui.DataType
        S16:    imgui.DataType
        U16:    imgui.DataType
        S32:    imgui.DataType
        U32:    imgui.DataType
        S64:    imgui.DataType
        U64:    imgui.DataType
        Float:  imgui.DataType
        Double: imgui.DataType
        Bool:   imgui.DataType
        String: imgui.DataType
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # Dir  (plain enum — no bitwise ops)
    # ------------------------------------------------------------------
    class Dir:
        None_:  imgui.Dir
        Left:   imgui.Dir
        Right:  imgui.Dir
        Up:     imgui.Dir
        Down:   imgui.Dir
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # SortDirection  (plain enum — no bitwise ops)
    # ------------------------------------------------------------------
    class SortDirection:
        None_:      imgui.SortDirection
        Ascending:  imgui.SortDirection
        Descending: imgui.SortDirection
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # Key  (bitmask — includes ImGuiMod values in the same int space)
    #
    # All names are prefixed "K_" to avoid clashes with Python builtins
    # (e.g. K_Tab, K_A).  Modifier names use "K_Mod_" prefix.
    # ------------------------------------------------------------------
    class Key:
        None_:              imgui.Key
        K_Tab:              imgui.Key
        K_LeftArrow:        imgui.Key
        K_RightArrow:       imgui.Key
        K_UpArrow:          imgui.Key
        K_DownArrow:        imgui.Key
        K_PageUp:           imgui.Key
        K_PageDown:         imgui.Key
        K_Home:             imgui.Key
        K_End:              imgui.Key
        K_Insert:           imgui.Key
        K_Delete:           imgui.Key
        K_Backspace:        imgui.Key
        K_Space:            imgui.Key
        K_Enter:            imgui.Key
        K_Escape:           imgui.Key
        K_LeftCtrl:         imgui.Key
        K_LeftShift:        imgui.Key
        K_LeftAlt:          imgui.Key
        K_LeftSuper:        imgui.Key
        K_RightCtrl:        imgui.Key
        K_RightShift:       imgui.Key
        K_RightAlt:         imgui.Key
        K_RightSuper:       imgui.Key
        K_Menu:             imgui.Key
        K_0:                imgui.Key
        K_1:                imgui.Key
        K_2:                imgui.Key
        K_3:                imgui.Key
        K_4:                imgui.Key
        K_5:                imgui.Key
        K_6:                imgui.Key
        K_7:                imgui.Key
        K_8:                imgui.Key
        K_9:                imgui.Key
        K_A:                imgui.Key
        K_B:                imgui.Key
        K_C:                imgui.Key
        K_D:                imgui.Key
        K_E:                imgui.Key
        K_F:                imgui.Key
        K_G:                imgui.Key
        K_H:                imgui.Key
        K_I:                imgui.Key
        K_J:                imgui.Key
        K_K:                imgui.Key
        K_L:                imgui.Key
        K_M:                imgui.Key
        K_N:                imgui.Key
        K_O:                imgui.Key
        K_P:                imgui.Key
        K_Q:                imgui.Key
        K_R:                imgui.Key
        K_S:                imgui.Key
        K_T:                imgui.Key
        K_U:                imgui.Key
        K_V:                imgui.Key
        K_W:                imgui.Key
        K_X:                imgui.Key
        K_Y:                imgui.Key
        K_Z:                imgui.Key
        K_F1:               imgui.Key
        K_F2:               imgui.Key
        K_F3:               imgui.Key
        K_F4:               imgui.Key
        K_F5:               imgui.Key
        K_F6:               imgui.Key
        K_F7:               imgui.Key
        K_F8:               imgui.Key
        K_F9:               imgui.Key
        K_F10:              imgui.Key
        K_F11:              imgui.Key
        K_F12:              imgui.Key
        K_F13:              imgui.Key
        K_F14:              imgui.Key
        K_F15:              imgui.Key
        K_F16:              imgui.Key
        K_F17:              imgui.Key
        K_F18:              imgui.Key
        K_F19:              imgui.Key
        K_F20:              imgui.Key
        K_F21:              imgui.Key
        K_F22:              imgui.Key
        K_F23:              imgui.Key
        K_F24:              imgui.Key
        K_Apostrophe:       imgui.Key
        K_Comma:            imgui.Key
        K_Minus:            imgui.Key
        K_Period:           imgui.Key
        K_Slash:            imgui.Key
        K_Semicolon:        imgui.Key
        K_Equal:            imgui.Key
        K_LeftBracket:      imgui.Key
        K_Backslash:        imgui.Key
        K_RightBracket:     imgui.Key
        K_GraveAccent:      imgui.Key
        K_CapsLock:         imgui.Key
        K_ScrollLock:       imgui.Key
        K_NumLock:          imgui.Key
        K_PrintScreen:      imgui.Key
        K_Pause:            imgui.Key
        K_Keypad0:          imgui.Key
        K_Keypad1:          imgui.Key
        K_Keypad2:          imgui.Key
        K_Keypad3:          imgui.Key
        K_Keypad4:          imgui.Key
        K_Keypad5:          imgui.Key
        K_Keypad6:          imgui.Key
        K_Keypad7:          imgui.Key
        K_Keypad8:          imgui.Key
        K_Keypad9:          imgui.Key
        K_KeypadDecimal:    imgui.Key
        K_KeypadDivide:     imgui.Key
        K_KeypadMultiply:   imgui.Key
        K_KeypadSubtract:   imgui.Key
        K_KeypadAdd:        imgui.Key
        K_KeypadEnter:      imgui.Key
        K_KeypadEqual:      imgui.Key
        K_AppBack:          imgui.Key
        K_AppForward:       imgui.Key
        K_Oem102:           imgui.Key
        K_GamepadStart:         imgui.Key
        K_GamepadBack:          imgui.Key
        K_GamepadFaceLeft:      imgui.Key
        K_GamepadFaceRight:     imgui.Key
        K_GamepadFaceUp:        imgui.Key
        K_GamepadFaceDown:      imgui.Key
        K_GamepadDpadLeft:      imgui.Key
        K_GamepadDpadRight:     imgui.Key
        K_GamepadDpadUp:        imgui.Key
        K_GamepadDpadDown:      imgui.Key
        K_GamepadL1:            imgui.Key
        K_GamepadR1:            imgui.Key
        K_GamepadL2:            imgui.Key
        K_GamepadR2:            imgui.Key
        K_GamepadL3:            imgui.Key
        K_GamepadR3:            imgui.Key
        K_GamepadLStickLeft:    imgui.Key
        K_GamepadLStickRight:   imgui.Key
        K_GamepadLStickUp:      imgui.Key
        K_GamepadLStickDown:    imgui.Key
        K_GamepadRStickLeft:    imgui.Key
        K_GamepadRStickRight:   imgui.Key
        K_GamepadRStickUp:      imgui.Key
        K_GamepadRStickDown:    imgui.Key
        K_MouseLeft:        imgui.Key
        K_MouseRight:       imgui.Key
        K_MouseMiddle:      imgui.Key
        K_MouseX1:          imgui.Key
        K_MouseX2:          imgui.Key
        K_MouseWheelX:      imgui.Key
        K_MouseWheelY:      imgui.Key
        # Modifier masks — share integer space with key codes
        K_Mod_None:         imgui.Key
        K_Mod_Ctrl:         imgui.Key
        K_Mod_Shift:        imgui.Key
        K_Mod_Alt:          imgui.Key
        K_Mod_Super:        imgui.Key
        K_Mod_Mask_:        imgui.Key
        def __or__(self, other: imgui.Key) -> imgui.Key: ...
        def __and__(self, other: imgui.Key) -> imgui.Key: ...
        def __xor__(self, other: imgui.Key) -> imgui.Key: ...
        def __invert__(self) -> imgui.Key: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # InputFlags  (bitmask)
    # ------------------------------------------------------------------
    class InputFlags:
        None_:                  imgui.InputFlags
        Repeat:                 imgui.InputFlags
        RouteActive:            imgui.InputFlags
        RouteFocused:           imgui.InputFlags
        RouteGlobal:            imgui.InputFlags
        RouteAlways:            imgui.InputFlags
        RouteOverFocused:       imgui.InputFlags
        RouteOverActive:        imgui.InputFlags
        RouteUnlessBgFocused:   imgui.InputFlags
        RouteFromRootWindow:    imgui.InputFlags
        Tooltip:                imgui.InputFlags
        def __or__(self, other: imgui.InputFlags) -> imgui.InputFlags: ...
        def __and__(self, other: imgui.InputFlags) -> imgui.InputFlags: ...
        def __xor__(self, other: imgui.InputFlags) -> imgui.InputFlags: ...
        def __invert__(self) -> imgui.InputFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # ConfigFlags  (bitmask)
    # ------------------------------------------------------------------
    class ConfigFlags:
        None_:               imgui.ConfigFlags
        NavEnableKeyboard:   imgui.ConfigFlags
        NavEnableGamepad:    imgui.ConfigFlags
        NoMouse:             imgui.ConfigFlags
        NoMouseCursorChange: imgui.ConfigFlags
        NoKeyboard:          imgui.ConfigFlags
        def __or__(self, other: imgui.ConfigFlags) -> imgui.ConfigFlags: ...
        def __and__(self, other: imgui.ConfigFlags) -> imgui.ConfigFlags: ...
        def __xor__(self, other: imgui.ConfigFlags) -> imgui.ConfigFlags: ...
        def __invert__(self) -> imgui.ConfigFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # Col  (plain enum — colour slot indices, no bitwise ops)
    # ------------------------------------------------------------------
    class Col:
        Text:                       imgui.Col
        TextDisabled:               imgui.Col
        WindowBg:                   imgui.Col
        ChildBg:                    imgui.Col
        PopupBg:                    imgui.Col
        Border:                     imgui.Col
        BorderShadow:               imgui.Col
        FrameBg:                    imgui.Col
        FrameBgHovered:             imgui.Col
        FrameBgActive:              imgui.Col
        TitleBg:                    imgui.Col
        TitleBgActive:              imgui.Col
        TitleBgCollapsed:           imgui.Col
        MenuBarBg:                  imgui.Col
        ScrollbarBg:                imgui.Col
        ScrollbarGrab:              imgui.Col
        ScrollbarGrabHovered:       imgui.Col
        ScrollbarGrabActive:        imgui.Col
        CheckMark:                  imgui.Col
        SliderGrab:                 imgui.Col
        SliderGrabActive:           imgui.Col
        Button:                     imgui.Col
        ButtonHovered:              imgui.Col
        ButtonActive:               imgui.Col
        Header:                     imgui.Col
        HeaderHovered:              imgui.Col
        HeaderActive:               imgui.Col
        Separator:                  imgui.Col
        SeparatorHovered:           imgui.Col
        SeparatorActive:            imgui.Col
        ResizeGrip:                 imgui.Col
        ResizeGripHovered:          imgui.Col
        ResizeGripActive:           imgui.Col
        InputTextCursor:            imgui.Col
        TabHovered:                 imgui.Col
        Tab:                        imgui.Col
        TabSelected:                imgui.Col
        TabSelectedOverline:        imgui.Col
        TabDimmed:                  imgui.Col
        TabDimmedSelected:          imgui.Col
        TabDimmedSelectedOverline:  imgui.Col
        PlotLines:                  imgui.Col
        PlotLinesHovered:           imgui.Col
        PlotHistogram:              imgui.Col
        PlotHistogramHovered:       imgui.Col
        TableHeaderBg:              imgui.Col
        TableBorderStrong:          imgui.Col
        TableBorderLight:           imgui.Col
        TableRowBg:                 imgui.Col
        TableRowBgAlt:              imgui.Col
        TextLink:                   imgui.Col
        TextSelectedBg:             imgui.Col
        TreeLines:                  imgui.Col
        DragDropTarget:             imgui.Col
        NavCursor:                  imgui.Col
        NavWindowingHighlight:      imgui.Col
        NavWindowingDimBg:          imgui.Col
        ModalWindowDimBg:           imgui.Col
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # StyleVar  (plain enum — style slot indices, no bitwise ops)
    # ------------------------------------------------------------------
    class StyleVar:
        Alpha:                          imgui.StyleVar
        DisabledAlpha:                  imgui.StyleVar
        WindowPadding:                  imgui.StyleVar
        WindowRounding:                 imgui.StyleVar
        WindowBorderSize:               imgui.StyleVar
        WindowMinSize:                  imgui.StyleVar
        WindowTitleAlign:               imgui.StyleVar
        ChildRounding:                  imgui.StyleVar
        ChildBorderSize:                imgui.StyleVar
        PopupRounding:                  imgui.StyleVar
        PopupBorderSize:                imgui.StyleVar
        FramePadding:                   imgui.StyleVar
        FrameRounding:                  imgui.StyleVar
        FrameBorderSize:                imgui.StyleVar
        ItemSpacing:                    imgui.StyleVar
        ItemInnerSpacing:               imgui.StyleVar
        IndentSpacing:                  imgui.StyleVar
        CellPadding:                    imgui.StyleVar
        ScrollbarSize:                  imgui.StyleVar
        ScrollbarRounding:              imgui.StyleVar
        GrabMinSize:                    imgui.StyleVar
        GrabRounding:                   imgui.StyleVar
        ImageBorderSize:                imgui.StyleVar
        TabRounding:                    imgui.StyleVar
        TabBorderSize:                  imgui.StyleVar
        TabBarBorderSize:               imgui.StyleVar
        TabBarOverlineSize:             imgui.StyleVar
        TableAngledHeadersAngle:        imgui.StyleVar
        TableAngledHeadersTextAlign:    imgui.StyleVar
        TreeLinesSize:                  imgui.StyleVar
        TreeLinesRounding:              imgui.StyleVar
        ButtonTextAlign:                imgui.StyleVar
        SelectableTextAlign:            imgui.StyleVar
        SeparatorTextBorderSize:        imgui.StyleVar
        SeparatorTextAlign:             imgui.StyleVar
        SeparatorTextPadding:           imgui.StyleVar
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # ButtonFlags  (bitmask)
    # ------------------------------------------------------------------
    class ButtonFlags:
        None_:              imgui.ButtonFlags
        MouseButtonLeft:    imgui.ButtonFlags
        MouseButtonRight:   imgui.ButtonFlags
        MouseButtonMiddle:  imgui.ButtonFlags
        MouseButtonMask_:   imgui.ButtonFlags
        EnableNav:          imgui.ButtonFlags
        def __or__(self, other: imgui.ButtonFlags) -> imgui.ButtonFlags: ...
        def __and__(self, other: imgui.ButtonFlags) -> imgui.ButtonFlags: ...
        def __xor__(self, other: imgui.ButtonFlags) -> imgui.ButtonFlags: ...
        def __invert__(self) -> imgui.ButtonFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # ColorEditFlags  (bitmask)
    # ------------------------------------------------------------------
    class ColorEditFlags:
        None_:              imgui.ColorEditFlags
        NoAlpha:            imgui.ColorEditFlags
        NoPicker:           imgui.ColorEditFlags
        NoOptions:          imgui.ColorEditFlags
        NoSmallPreview:     imgui.ColorEditFlags
        NoInputs:           imgui.ColorEditFlags
        NoTooltip:          imgui.ColorEditFlags
        NoLabel:            imgui.ColorEditFlags
        NoSidePreview:      imgui.ColorEditFlags
        NoDragDrop:         imgui.ColorEditFlags
        NoBorder:           imgui.ColorEditFlags
        AlphaOpaque:        imgui.ColorEditFlags
        AlphaNoBg:          imgui.ColorEditFlags
        AlphaPreviewHalf:   imgui.ColorEditFlags
        AlphaBar:           imgui.ColorEditFlags
        HDR:                imgui.ColorEditFlags
        DisplayRGB:         imgui.ColorEditFlags
        DisplayHSV:         imgui.ColorEditFlags
        DisplayHex:         imgui.ColorEditFlags
        Uint8:              imgui.ColorEditFlags
        Float:              imgui.ColorEditFlags
        PickerHueBar:       imgui.ColorEditFlags
        PickerHueWheel:     imgui.ColorEditFlags
        InputRGB:           imgui.ColorEditFlags
        InputHSV:           imgui.ColorEditFlags
        DefaultOptions_:    imgui.ColorEditFlags
        AlphaMask_:         imgui.ColorEditFlags
        DisplayMask_:       imgui.ColorEditFlags
        DataTypeMask_:      imgui.ColorEditFlags
        PickerMask_:        imgui.ColorEditFlags
        InputMask_:         imgui.ColorEditFlags
        def __or__(self, other: imgui.ColorEditFlags) -> imgui.ColorEditFlags: ...
        def __and__(self, other: imgui.ColorEditFlags) -> imgui.ColorEditFlags: ...
        def __xor__(self, other: imgui.ColorEditFlags) -> imgui.ColorEditFlags: ...
        def __invert__(self) -> imgui.ColorEditFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # SliderFlags  (bitmask)
    # ------------------------------------------------------------------
    class SliderFlags:
        None_:           imgui.SliderFlags
        Logarithmic:     imgui.SliderFlags
        NoRoundToFormat: imgui.SliderFlags
        NoInput:         imgui.SliderFlags
        WrapAround:      imgui.SliderFlags
        ClampOnInput:    imgui.SliderFlags
        ClampZeroRange:  imgui.SliderFlags
        NoSpeedTweaks:   imgui.SliderFlags
        AlwaysClamp:     imgui.SliderFlags
        InvalidMask_:    imgui.SliderFlags
        def __or__(self, other: imgui.SliderFlags) -> imgui.SliderFlags: ...
        def __and__(self, other: imgui.SliderFlags) -> imgui.SliderFlags: ...
        def __xor__(self, other: imgui.SliderFlags) -> imgui.SliderFlags: ...
        def __invert__(self) -> imgui.SliderFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # MouseButton  (plain enum — no bitwise ops)
    # ------------------------------------------------------------------
    class MouseButton:
        Left:   imgui.MouseButton
        Right:  imgui.MouseButton
        Middle: imgui.MouseButton
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # MouseCursor  (plain enum — None_ = -1 sentinel, no bitwise ops)
    # ------------------------------------------------------------------
    class MouseCursor:
        None_:      imgui.MouseCursor
        Arrow:      imgui.MouseCursor
        TextInput:  imgui.MouseCursor
        ResizeAll:  imgui.MouseCursor
        ResizeNS:   imgui.MouseCursor
        ResizeEW:   imgui.MouseCursor
        ResizeNESW: imgui.MouseCursor
        ResizeNWSE: imgui.MouseCursor
        Hand:       imgui.MouseCursor
        Wait:       imgui.MouseCursor
        Progress:   imgui.MouseCursor
        NotAllowed: imgui.MouseCursor
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # Cond  (plain enum — exclusive conditions, no bitwise ops)
    # ------------------------------------------------------------------
    class Cond:
        None_:        imgui.Cond
        Always:       imgui.Cond
        Once:         imgui.Cond
        FirstUseEver: imgui.Cond
        Appearing:    imgui.Cond
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TableFlags  (bitmask)
    # ------------------------------------------------------------------
    class TableFlags:
        None_:                      imgui.TableFlags
        Resizable:                  imgui.TableFlags
        Reorderable:                imgui.TableFlags
        Hideable:                   imgui.TableFlags
        Sortable:                   imgui.TableFlags
        NoSavedSettings:            imgui.TableFlags
        ContextMenuInBody:          imgui.TableFlags
        RowBg:                      imgui.TableFlags
        BordersInnerH:              imgui.TableFlags
        BordersOuterH:              imgui.TableFlags
        BordersInnerV:              imgui.TableFlags
        BordersOuterV:              imgui.TableFlags
        BordersH:                   imgui.TableFlags  # InnerH | OuterH
        BordersV:                   imgui.TableFlags  # InnerV | OuterV
        BordersInner:               imgui.TableFlags  # InnerH | InnerV
        BordersOuter:               imgui.TableFlags  # OuterH | OuterV
        Borders:                    imgui.TableFlags  # InnerH | InnerV | OuterH | OuterV
        NoBordersInBody:            imgui.TableFlags
        NoBordersInBodyUntilResize: imgui.TableFlags
        SizingFixedFit:             imgui.TableFlags
        SizingFixedSame:            imgui.TableFlags
        SizingStretchProp:          imgui.TableFlags
        SizingStretchSame:          imgui.TableFlags
        NoHostExtendX:              imgui.TableFlags
        NoHostExtendY:              imgui.TableFlags
        NoKeepColumnsVisible:       imgui.TableFlags
        PreciseWidths:              imgui.TableFlags
        NoClip:                     imgui.TableFlags
        PadOuterX:                  imgui.TableFlags
        NoPadOuterX:                imgui.TableFlags
        NoPadInnerX:                imgui.TableFlags
        ScrollX:                    imgui.TableFlags
        ScrollY:                    imgui.TableFlags
        SortMulti:                  imgui.TableFlags
        SortTristate:               imgui.TableFlags
        HighlightHoveredColumn:     imgui.TableFlags
        def __or__(self, other: imgui.TableFlags) -> imgui.TableFlags: ...
        def __and__(self, other: imgui.TableFlags) -> imgui.TableFlags: ...
        def __xor__(self, other: imgui.TableFlags) -> imgui.TableFlags: ...
        def __invert__(self) -> imgui.TableFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TableColumnFlags  (bitmask)
    # ------------------------------------------------------------------
    class TableColumnFlags:
        None_:                  imgui.TableColumnFlags
        Disabled:               imgui.TableColumnFlags
        DefaultHide:            imgui.TableColumnFlags
        DefaultSort:            imgui.TableColumnFlags
        WidthStretch:           imgui.TableColumnFlags
        WidthFixed:             imgui.TableColumnFlags
        NoResize:               imgui.TableColumnFlags
        NoReorder:              imgui.TableColumnFlags
        NoHide:                 imgui.TableColumnFlags
        NoClip:                 imgui.TableColumnFlags
        NoSort:                 imgui.TableColumnFlags
        NoSortAscending:        imgui.TableColumnFlags
        NoSortDescending:       imgui.TableColumnFlags
        NoHeaderLabel:          imgui.TableColumnFlags
        NoHeaderWidth:          imgui.TableColumnFlags
        PreferSortAscending:    imgui.TableColumnFlags
        PreferSortDescending:   imgui.TableColumnFlags
        IndentEnable:           imgui.TableColumnFlags
        IndentDisable:          imgui.TableColumnFlags
        AngledHeader:           imgui.TableColumnFlags
        IsEnabled:              imgui.TableColumnFlags  # read-only output flag
        IsVisible:              imgui.TableColumnFlags  # read-only output flag
        IsSorted:               imgui.TableColumnFlags  # read-only output flag
        IsHovered:              imgui.TableColumnFlags  # read-only output flag
        def __or__(self, other: imgui.TableColumnFlags) -> imgui.TableColumnFlags: ...
        def __and__(self, other: imgui.TableColumnFlags) -> imgui.TableColumnFlags: ...
        def __xor__(self, other: imgui.TableColumnFlags) -> imgui.TableColumnFlags: ...
        def __invert__(self) -> imgui.TableColumnFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TableRowFlags  (bitmask)
    # ------------------------------------------------------------------
    class TableRowFlags:
        None_:   imgui.TableRowFlags
        Headers: imgui.TableRowFlags
        def __or__(self, other: imgui.TableRowFlags) -> imgui.TableRowFlags: ...
        def __and__(self, other: imgui.TableRowFlags) -> imgui.TableRowFlags: ...
        def __xor__(self, other: imgui.TableRowFlags) -> imgui.TableRowFlags: ...
        def __invert__(self) -> imgui.TableRowFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # TableBgTarget  (bitmask)
    # ------------------------------------------------------------------
    class TableBgTarget:
        None_:  imgui.TableBgTarget
        RowBg0: imgui.TableBgTarget
        RowBg1: imgui.TableBgTarget
        CellBg: imgui.TableBgTarget
        def __or__(self, other: imgui.TableBgTarget) -> imgui.TableBgTarget: ...
        def __and__(self, other: imgui.TableBgTarget) -> imgui.TableBgTarget: ...
        def __xor__(self, other: imgui.TableBgTarget) -> imgui.TableBgTarget: ...
        def __invert__(self) -> imgui.TableBgTarget: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # MultiSelectFlags  (bitmask)
    # ------------------------------------------------------------------
    class MultiSelectFlags:
        None_:                  imgui.MultiSelectFlags
        SingleSelect:           imgui.MultiSelectFlags
        NoSelectAll:            imgui.MultiSelectFlags
        NoRangeSelect:          imgui.MultiSelectFlags
        NoAutoSelect:           imgui.MultiSelectFlags
        NoAutoClear:            imgui.MultiSelectFlags
        NoAutoClearOnReselect:  imgui.MultiSelectFlags
        BoxSelect1d:            imgui.MultiSelectFlags
        BoxSelect2d:            imgui.MultiSelectFlags
        BoxSelectNoScroll:      imgui.MultiSelectFlags
        ClearOnEscape:          imgui.MultiSelectFlags
        ClearOnClickVoid:       imgui.MultiSelectFlags
        ScopeWindow:            imgui.MultiSelectFlags
        ScopeRect:              imgui.MultiSelectFlags
        SelectOnClick:          imgui.MultiSelectFlags
        SelectOnClickRelease:   imgui.MultiSelectFlags
        def __or__(self, other: imgui.MultiSelectFlags) -> imgui.MultiSelectFlags: ...
        def __and__(self, other: imgui.MultiSelectFlags) -> imgui.MultiSelectFlags: ...
        def __xor__(self, other: imgui.MultiSelectFlags) -> imgui.MultiSelectFlags: ...
        def __invert__(self) -> imgui.MultiSelectFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # SelectionRequestType  (plain enum — no bitwise ops)
    # ------------------------------------------------------------------
    class SelectionRequestType:
        None_:    imgui.SelectionRequestType
        SetAll:   imgui.SelectionRequestType
        SetRange: imgui.SelectionRequestType
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # DrawFlags  (bitmask)
    # ------------------------------------------------------------------
    class DrawFlags:
        None_:                   imgui.DrawFlags
        Closed:                  imgui.DrawFlags
        RoundCornersTopLeft:     imgui.DrawFlags
        RoundCornersTopRight:    imgui.DrawFlags
        RoundCornersBottomLeft:  imgui.DrawFlags
        RoundCornersBottomRight: imgui.DrawFlags
        RoundCornersNone:        imgui.DrawFlags
        RoundCornersTop:         imgui.DrawFlags  # TopLeft | TopRight
        RoundCornersBottom:      imgui.DrawFlags  # BottomLeft | BottomRight
        RoundCornersLeft:        imgui.DrawFlags  # TopLeft | BottomLeft
        RoundCornersRight:       imgui.DrawFlags  # TopRight | BottomRight
        RoundCornersAll:         imgui.DrawFlags  # all four corners
        RoundCornersDefault_:    imgui.DrawFlags  # = RoundCornersAll
        RoundCornersMask_:       imgui.DrawFlags
        def __or__(self, other: imgui.DrawFlags) -> imgui.DrawFlags: ...
        def __and__(self, other: imgui.DrawFlags) -> imgui.DrawFlags: ...
        def __xor__(self, other: imgui.DrawFlags) -> imgui.DrawFlags: ...
        def __invert__(self) -> imgui.DrawFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # DrawListFlags  (bitmask)
    # ------------------------------------------------------------------
    class DrawListFlags:
        None_:                   imgui.DrawListFlags
        AntiAliasedLines:        imgui.DrawListFlags
        AntiAliasedLinesUseTex:  imgui.DrawListFlags
        AntiAliasedFill:         imgui.DrawListFlags
        AllowVtxOffset:          imgui.DrawListFlags
        def __or__(self, other: imgui.DrawListFlags) -> imgui.DrawListFlags: ...
        def __and__(self, other: imgui.DrawListFlags) -> imgui.DrawListFlags: ...
        def __xor__(self, other: imgui.DrawListFlags) -> imgui.DrawListFlags: ...
        def __invert__(self) -> imgui.DrawListFlags: ...
        def __int__(self) -> int: ...

    # ------------------------------------------------------------------
    # FontAtlasFlags  (bitmask)
    # ------------------------------------------------------------------
    class FontAtlasFlags:
        None_:               imgui.FontAtlasFlags
        NoPowerOfTwoHeight:  imgui.FontAtlasFlags
        NoMouseCursors:      imgui.FontAtlasFlags
        NoBakedLines:        imgui.FontAtlasFlags
        def __or__(self, other: imgui.FontAtlasFlags) -> imgui.FontAtlasFlags: ...
        def __and__(self, other: imgui.FontAtlasFlags) -> imgui.FontAtlasFlags: ...
        def __xor__(self, other: imgui.FontAtlasFlags) -> imgui.FontAtlasFlags: ...
        def __invert__(self) -> imgui.FontAtlasFlags: ...
        def __int__(self) -> int: ...

    # ==================================================================
    # Structs & Classes
    # ==================================================================

    # ------------------------------------------------------------------
    # Vec2
    # ------------------------------------------------------------------
    class Vec2:
        x: float
        y: float

        def __init__(self, x: float = 0.0, y: float = 0.0) -> None: ...
        def __repr__(self) -> str: ...
        def __eq__(self, other: imgui.Vec2) -> bool: ...

    # ------------------------------------------------------------------
    # Vec4
    # ------------------------------------------------------------------
    class Vec4:
        x: float
        y: float
        z: float
        w: float

        def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0, w: float = 0.0) -> None: ...
        def __repr__(self) -> str: ...
        def __eq__(self, other: imgui.Vec4) -> bool: ...

    # ------------------------------------------------------------------
    # Color
    # ------------------------------------------------------------------
    class Color:
        r: float
        g: float
        b: float
        a: float
        value: imgui.Vec4  # direct access to underlying ImVec4

        @overload
        def __init__(self, r: float, g: float, b: float, a: float = 1.0) -> None: ...
        @overload
        def __init__(self, vec: imgui.Vec4) -> None: ...

        def to_vec4(self) -> imgui.Vec4:
            """Return the colour as a Vec4 (convenience alias for .value)."""
            ...

    # ------------------------------------------------------------------
    # IO
    # ------------------------------------------------------------------
    class IO:
        # Display / timing
        display_size:               imgui.Vec2
        delta_time:                 float
        ini_saving_rate:            float
        font_global_scale:          float
        display_framebuffer_scale:  imgui.Vec2

        # Mouse / keyboard state
        mouse_draw_cursor:           bool
        mouse_wheel:                 float
        mouse_wheel_h:               float
        mouse_down:                  list[bool]  # 5-element list
        mouse_double_click_time:     float
        mouse_double_click_max_dist: float
        mouse_drag_threshold:        float
        want_set_mouse_pos:          bool

        key_ctrl:         bool
        key_shift:        bool
        key_alt:          bool
        key_super:        bool
        key_repeat_delay: float
        key_repeat_rate:  float

        # Config flags — properly typed
        config_flags:   imgui.ConfigFlags
        backend_flags:  int  # ImGuiBackendFlags — not bound as an enum
        config_nav_swap_gamepad_buttons:         bool
        config_nav_move_set_mouse_pos:           bool
        config_nav_capture_keyboard:             bool
        config_nav_escape_clear_focus_item:      bool
        config_nav_escape_clear_focus_window:    bool
        config_nav_cursor_visible_auto:          bool
        config_nav_cursor_visible_always:        bool
        config_input_trickle_event_queue:        bool
        config_input_text_cursor_blink:          bool
        config_input_text_enter_keep_active:     bool
        config_drag_click_to_input_text:         bool
        config_windows_resize_from_edges:        bool
        config_windows_move_from_title_bar_only: bool
        config_scrollbar_scroll_by_page:         bool

        # Read-only output fields
        @property
        def framerate(self) -> float: ...
        @property
        def want_capture_mouse(self) -> bool: ...
        @property
        def want_capture_keyboard(self) -> bool: ...
        @property
        def want_text_input(self) -> bool: ...
        @property
        def nav_active(self) -> bool: ...
        @property
        def nav_visible(self) -> bool: ...

        # Font access
        font_default: imgui.Font  # read-write, reference
        @property
        def fonts(self) -> imgui.FontAtlas: ...  # read-only, reference

        # File paths (heap-owned by binding layer after first set)
        ini_filename: str
        log_filename: str

    # ------------------------------------------------------------------
    # Style
    # ------------------------------------------------------------------
        # Scalar style values
        alpha:                               float
        disabled_alpha:                      float
        window_rounding:                     float
        window_border_size:                  float
        window_border_hover_padding:         float
        child_rounding:                      float
        child_border_size:                   float
        popup_rounding:                      float
        popup_border_size:                   float
        frame_rounding:                      float
        frame_border_size:                   float
        indent_spacing:                      float
        columns_min_spacing:                 float
        scrollbar_size:                      float
        scrollbar_rounding:                  float
        grab_min_size:                       float
        grab_rounding:                       float
        log_slider_deadzone:                 float
        image_border_size:                   float
        tab_rounding:                        float
        tab_border_size:                     float
        tab_close_button_min_width_selected:   float
        tab_close_button_min_width_unselected: float
        tab_bar_border_size:                 float
        tab_bar_overline_size:               float
        table_angled_headers_angle:          float
        tree_lines_size:                     float
        tree_lines_rounding:                 float
        separator_text_border_size:          float
        mouse_cursor_scale:                  float
        curve_tessellation_tol:              float
        circle_tessellation_max_error:       float
        hover_stationary_delay:              float
        hover_delay_short:                   float
        hover_delay_normal:                  float

        # Boolean style flags
        anti_aliased_lines:         bool
        anti_aliased_lines_use_tex: bool
        anti_aliased_fill:          bool

        # Vec2 style values
        window_padding:                  imgui.Vec2
        window_min_size:                 imgui.Vec2
        window_title_align:              imgui.Vec2
        frame_padding:                   imgui.Vec2
        item_spacing:                    imgui.Vec2
        item_inner_spacing:              imgui.Vec2
        cell_padding:                    imgui.Vec2
        touch_extra_padding:             imgui.Vec2
        table_angled_headers_text_align: imgui.Vec2
        button_text_align:               imgui.Vec2
        selectable_text_align:           imgui.Vec2
        separator_text_align:            imgui.Vec2
        separator_text_padding:          imgui.Vec2
        display_window_padding:          imgui.Vec2
        display_safe_area_padding:       imgui.Vec2

        # Enum-typed style values — properly typed
        window_menu_button_position:   imgui.Dir
        color_button_position:         imgui.Dir
        tree_lines_flags:              imgui.TreeNodeFlags
        hover_flags_for_tooltip_mouse: imgui.HoveredFlags
        hover_flags_for_tooltip_nav:   imgui.HoveredFlags

        # Color table — index with imgui.Col.*
        colors: list[imgui.Vec4]

        def scale_all_sizes(self, scale_factor: float) -> None: ...

    # ------------------------------------------------------------------
    # DrawList
    # ------------------------------------------------------------------
        flags: imgui.DrawListFlags

        # Primitives
        def add_line(self, p1: imgui.Vec2, p2: imgui.Vec2, col: int, thickness: float = 1.0) -> None: ...
        def add_rect(self, p_min: imgui.Vec2, p_max: imgui.Vec2, col: int, rounding: float = 0.0, flags: imgui.DrawFlags = ..., thickness: float = 1.0) -> None: ...
        def add_rect_filled(self, p_min: imgui.Vec2, p_max: imgui.Vec2, col: int, rounding: float = 0.0, flags: imgui.DrawFlags = ...) -> None: ...
        def add_circle(self, center: imgui.Vec2, radius: float, col: int, num_segments: int = 0, thickness: float = 1.0) -> None: ...
        def add_circle_filled(self, center: imgui.Vec2, radius: float, col: int, num_segments: int = 0) -> None: ...
        def add_triangle(self, p1: imgui.Vec2, p2: imgui.Vec2, p3: imgui.Vec2, col: int, thickness: float = 1.0) -> None: ...
        def add_triangle_filled(self, p1: imgui.Vec2, p2: imgui.Vec2, p3: imgui.Vec2, col: int) -> None: ...
        def add_ngon(self, center: imgui.Vec2, radius: float, col: int, num_segments: int, thickness: float = 1.0) -> None: ...
        def add_ngon_filled(self, center: imgui.Vec2, radius: float, col: int, num_segments: int) -> None: ...
        def add_quad(self, p1: imgui.Vec2, p2: imgui.Vec2, p3: imgui.Vec2, p4: imgui.Vec2, col: int, thickness: float = 1.0) -> None: ...
        def add_quad_filled(self, p1: imgui.Vec2, p2: imgui.Vec2, p3: imgui.Vec2, p4: imgui.Vec2, col: int) -> None: ...
        def add_text(self, pos: imgui.Vec2, col: int, text: str) -> None: ...
        def add_bezier_cubic(self, p1: imgui.Vec2, p2: imgui.Vec2, p3: imgui.Vec2, p4: imgui.Vec2, col: int, thickness: float, num_segments: int = 0) -> None: ...
        def add_bezier_quadratic(self, p1: imgui.Vec2, p2: imgui.Vec2, p3: imgui.Vec2, col: int, thickness: float, num_segments: int = 0) -> None: ...

        # Clip rects
        def push_clip_rect(self, min: imgui.Vec2, max: imgui.Vec2, intersect_with_current: bool = False) -> None: ...
        def pop_clip_rect(self) -> None: ...
        def get_clip_rect_min(self) -> imgui.Vec2: ...
        def get_clip_rect_max(self) -> imgui.Vec2: ...

        # Textures
        def push_texture_id(self, texture_id: int) -> None: ...
        def pop_texture_id(self) -> None: ...

        # Path API
        def path_clear(self) -> None: ...
        def path_line_to(self, pos: imgui.Vec2) -> None: ...
        def path_fill_convex(self, col: int) -> None: ...
        def path_stroke(self, col: int, flags: imgui.DrawFlags = ..., thickness: float = 1.0) -> None: ...

        def clone_output(self) -> imgui.DrawList:
            """Return a heap-allocated clone. Caller is responsible for lifetime."""
            ...

    # ------------------------------------------------------------------
    # Viewport
    # ------------------------------------------------------------------
    class Viewport:
        @property
        def id(self) -> int: ...
        @property
        def flags(self) -> int: ...

        pos:       imgui.Vec2
        size:      imgui.Vec2
        work_pos:  imgui.Vec2
        work_size: imgui.Vec2

        @property
        def platform_handle(self) -> int: ...
        @property
        def platform_handle_raw(self) -> int: ...

        def get_center(self) -> imgui.Vec2: ...
        def get_work_center(self) -> imgui.Vec2: ...

    # ------------------------------------------------------------------
    # FontConfig
    # ------------------------------------------------------------------
    class FontConfig:
        font_data:               int    # void* — raw pointer
        font_data_size:          int
        font_data_owned_by_atlas: bool
        merge_mode:              bool
        pixel_snap_h:            bool
        font_no:                 int
        oversample_h:            int
        oversample_v:            int
        size_pixels:             float
        glyph_offset:            imgui.Vec2
        glyph_ranges:            int    # const ImWchar* — raw pointer
        glyph_min_advance_x:     float
        glyph_max_advance_x:     float
        glyph_extra_advance_x:   float
        font_builder_flags:      int
        rasterizer_multiply:     float
        rasterizer_density:      float
        ellipsis_char:           int    # ImWchar
        name:                    str    # clamped to internal buffer size
        dst_font:                imgui.Font  # reference

        def __init__(self) -> None: ...

    # ------------------------------------------------------------------
    # FontGlyph
    # ------------------------------------------------------------------
    class FontGlyph:
        colored:   bool
        visible:   bool
        codepoint: int
        advance_x: float
        x0: float
        y0: float
        x1: float
        y1: float
        u0: float
        v0: float
        u1: float
        v1: float

    # ------------------------------------------------------------------
    # FontGlyphRangesBuilder
    # ------------------------------------------------------------------
    class FontGlyphRangesBuilder:
        def __init__(self) -> None: ...
        def clear(self) -> None: ...
        def get_bit(self, n: int) -> bool: ...
        def set_bit(self, n: int) -> None: ...
        def add_char(self, c: int) -> None: ...
        def add_text(self, text: str, text_end: Optional[str] = None) -> None: ...
        def add_ranges(self, ranges: int) -> None: ...  # const ImWchar* pointer
        def build_ranges(self) -> list[int]:
            """
            Build and return the packed glyph ranges as a list of ImWchar values.
            Terminated by a 0 sentinel, matching ImGui's convention.
            Pass to ctypes to get a raw pointer for use with font loading APIs.
            """
            ...

    # ------------------------------------------------------------------
    # FontAtlasCustomRect
    # ------------------------------------------------------------------
    class FontAtlasCustomRect:
        x:               int
        y:               int
        width:           int
        height:          int
        glyph_id:        int
        glyph_colored:   bool
        glyph_advance_x: float
        glyph_offset:    imgui.Vec2
        font:            imgui.Font  # reference

        def __init__(self) -> None: ...
        def is_packed(self) -> bool: ...

    # ------------------------------------------------------------------
    # FontAtlas
    # ------------------------------------------------------------------
    class FontAtlas:
        flags:              imgui.FontAtlasFlags
        tex_id:             int   # ImTextureID
        tex_desired_width:  int
        tex_glyph_padding:  int
        user_data:          int   # void* — raw pointer
        tex_width:          int
        tex_height:         int
        tex_uv_scale:       imgui.Vec2
        tex_uv_white_pixel: imgui.Vec2
        fonts:              list[imgui.Font]
        custom_rects:       list[imgui.FontAtlasCustomRect]
        sources:            list[imgui.FontConfig]  # ImFontAtlasSources

        def __init__(self) -> None: ...

        def add_font(self, font_cfg: imgui.FontConfig) -> imgui.Font: ...
        def add_font_default(self, font_cfg: Optional[imgui.FontConfig] = None) -> imgui.Font: ...

        def add_font_from_file_ttf(
            self,
            filename: str,
            size_pixels: float,
            font_cfg: Optional[imgui.FontConfig] = None,
            glyph_ranges: Optional[int] = None,
        ) -> imgui.Font: ...

        def add_font_from_memory_ttf(
            self,
            font_data: bytes,
            size_pixels: float,
            font_cfg: Optional[imgui.FontConfig] = None,
            glyph_ranges: Optional[int] = None,
        ) -> imgui.Font:
            """
            Load a font from raw TTF bytes.
            ImGui takes ownership of the data; the binding allocates a copy via
            IM_ALLOC so that ImGui can safely free it later.
            """
            ...

        def add_font_from_memory_compressed_ttf(
            self,
            data: bytes,
            size_pixels: float,
            font_cfg: Optional[imgui.FontConfig] = None,
            glyph_ranges: Optional[int] = None,
        ) -> imgui.Font: ...

        def add_font_from_memory_compressed_base85_ttf(
            self,
            data_base85: str,
            size_pixels: float,
            font_cfg: Optional[imgui.FontConfig] = None,
            glyph_ranges: Optional[int] = None,
        ) -> imgui.Font: ...

        # Glyph range helpers — return raw ImWchar* pointers (as int)
        def get_glyph_ranges_default(self) -> int: ...
        def get_glyph_ranges_greek(self) -> int: ...
        def get_glyph_ranges_korean(self) -> int: ...
        def get_glyph_ranges_japanese(self) -> int: ...
        def get_glyph_ranges_chinese_full(self) -> int: ...
        def get_glyph_ranges_chinese_simplified_common(self) -> int: ...
        def get_glyph_ranges_cyrillic(self) -> int: ...
        def get_glyph_ranges_thai(self) -> int: ...
        def get_glyph_ranges_vietnamese(self) -> int: ...

        def get_tex_data_as_rgba32(self) -> bytes:
            """Return raw RGBA32 pixel data for the atlas texture."""
            ...

        def get_tex_data_as_alpha8(self) -> bytes:
            """Return raw Alpha8 pixel data for the atlas texture."""
            ...

        def is_built(self) -> bool: ...
        def set_tex_id(self, id: int) -> None: ...
        def clear(self) -> None: ...
        def clear_fonts(self) -> None: ...
        def clear_input_data(self) -> None: ...
        def clear_tex_data(self) -> None: ...
        def build(self) -> bool: ...

        def add_custom_rect_regular(self, width: int, height: int) -> int: ...
        def add_custom_rect_font_glyph(
            self,
            font: imgui.Font,
            id: int,
            width: int,
            height: int,
            advance_x: float,
            offset: imgui.Vec2 = ...,
        ) -> int: ...
        def get_custom_rect_by_index(self, index: int) -> imgui.FontAtlasCustomRect: ...

    # ------------------------------------------------------------------
    # Font
    # ------------------------------------------------------------------
    class Font:
        fallback_advance_x:    float
        font_size:             float
        fallback_glyph:        imgui.FontGlyph  # reference
        fallback_char:         int              # ImWchar
        scale:                 float
        ascent:                float
        descent:               float
        ellipsis_char:         int              # ImWchar
        ellipsis_char_count:   int
        ellipsis_width:        float
        ellipsis_char_step:    float
        metrics_total_surface: int
        dirty_lookup_tables:   bool

        def find_glyph(self, c: int) -> imgui.FontGlyph: ...
        def find_glyph_no_fallback(self, c: int) -> imgui.FontGlyph: ...
        def get_char_advance(self, c: int) -> float: ...
        def is_loaded(self) -> bool: ...
        def get_debug_name(self) -> str: ...

        def calc_text_size_a(
            self,
            size: float,
            max_width: float,
            wrap_width: float,
            text: str,
            text_end: Optional[int] = None,
        ) -> imgui.Vec2:
            """
            Calculate the rendered size of a string.

            ``text_end`` is an optional integer byte offset into ``text``
            marking the end of the substring to measure.  When omitted the
            whole string is measured.
            """
            ...

        def render_char(
            self,
            draw_list: imgui.DrawList,
            size: float,
            pos: imgui.Vec2,
            col: int,
            c: int,
        ) -> None: ...

        def render_text(
            self,
            draw_list: imgui.DrawList,
            size: float,
            pos: imgui.Vec2,
            col: int,
            clip_rect: imgui.Vec4,
            text_begin: str,
            text_end: str,
            wrap_width: float = 0.0,
            cpu_fine_clip: bool = False,
        ) -> None: ...

    # ==================================================================
    # Free functions  (bound onto the imgui module / class)
    # ==================================================================

    # ------------------------------------------------------------------
    # Window
    # ------------------------------------------------------------------
    def begin(
        name: str,
        p_open: Optional[bool] = None,
        flags: imgui.WindowFlags = ...,
    ) -> Tuple[bool, Optional[bool]]:
        """
        Begin a new window.

        p_open controls the close button:
          - None  → no close button, returns (visible, None)
          - bool  → shows close button, returns (visible, is_still_open)

        Always call end() regardless of the return value.
        """
        ...

    def end() -> None: ...

    # ------------------------------------------------------------------
    # Text
    # ------------------------------------------------------------------
    def text(text: str) -> None: ...

    def text_colored(color: imgui.Vec4, text: str) -> None: ...

    # ------------------------------------------------------------------
    # Styling
    # ------------------------------------------------------------------
    def push_style_color(idx: imgui.Col, color: imgui.Vec4) -> None: ...
    def pop_style_color(count: int = 1) -> None: ...

    def push_style_var_float(idx: imgui.StyleVar, value: float) -> None: ...
    def push_style_var_vec2(idx: imgui.StyleVar, value: imgui.Vec2) -> None: ...
    def pop_style_var(count: int = 1) -> None: ...

    def push_item_width(width: float) -> None: ...
    def pop_item_width() -> None: ...
    def set_next_item_width(width: float) -> None: ...

    def indent(indent_w: float = 0.0) -> None: ...
    def unindent(indent_w: float = 0.0) -> None: ...

    def begin_group() -> None: ...
    def end_group() -> None: ...

    # ------------------------------------------------------------------
    # Layout / Spacing
    # ------------------------------------------------------------------
    def same_line(offset_from_start_x: float = 0.0, spacing: float = -1.0) -> None:
        """
        Call between widgets to place the next one on the same line.
        spacing = -1.0 means "use current style ItemSpacing.x" (the ImGui default).
        spacing = 0.0 means literally zero pixels between items.
        """
        ...

    def dummy(size: imgui.Vec2) -> None: ...
    def separator() -> None: ...
    def spacing() -> None: ...

    # ------------------------------------------------------------------
    # Next-window setup
    # ------------------------------------------------------------------
    def set_next_window_pos(
        pos: imgui.Vec2,
        cond: imgui.Cond = ...,
        pivot: imgui.Vec2 = ...,
    ) -> None: ...

    def set_next_window_size(
        size: imgui.Vec2,
        cond: imgui.Cond = ...,
    ) -> None: ...

    def set_next_window_size_constraints(
        size_min: imgui.Vec2,
        size_max: imgui.Vec2,
    ) -> None: ...

    def set_next_window_content_size(size: imgui.Vec2) -> None: ...

    def set_next_window_collapsed(
        collapsed: bool,
        cond: imgui.Cond = ...,
    ) -> None: ...

    def set_next_window_focus() -> None: ...

    # ------------------------------------------------------------------
    # Cursor / Item focus
    # ------------------------------------------------------------------
    def set_cursor_pos(local_pos: imgui.Vec2) -> None: ...
    def set_cursor_screen_pos(screen_pos: imgui.Vec2) -> None: ...
    def set_item_default_focus() -> None: ...

    # ------------------------------------------------------------------
    # Basic widgets
    # ------------------------------------------------------------------
    def button(label: str, size: imgui.Vec2 = ...) -> bool: ...
    def small_button(label: str) -> bool: ...
    def arrow_button(str_id: str, dir: imgui.Dir) -> bool: ...

    def invisible_button(
        str_id: str,
        size: imgui.Vec2,
        flags: imgui.ButtonFlags = ...,
    ) -> bool: ...

    def color_button(
        desc_id: str,
        color: imgui.Vec4,
        flags: imgui.ColorEditFlags = ...,
        size: imgui.Vec2 = ...,
    ) -> bool: ...

    def checkbox(label: str, value: bool) -> Tuple[bool, bool]:
        """Returns (changed, new_value)."""
        ...

    def radio_button(
        label: str,
        current_value: int,
        button_value: int,
    ) -> Tuple[bool, int]:
        """Returns (changed, current_value). current_value is updated to button_value if clicked."""
        ...

    # ------------------------------------------------------------------
    # Text inputs
    # ------------------------------------------------------------------
    def input_text(
        label: str,
        text: str,
        flags: imgui.InputTextFlags = ...,
    ) -> Tuple[bool, str]:
        """Returns (changed, new_text)."""
        ...

    def input_text_with_hint(
        label: str,
        hint: str,
        text: str,
        flags: imgui.InputTextFlags = ...,
    ) -> Tuple[bool, str]:
        """Returns (changed, new_text)."""
        ...

    def input_text_multiline(
        label: str,
        text: str,
        size: imgui.Vec2 = ...,
        flags: imgui.InputTextFlags = ...,
    ) -> Tuple[bool, str]:
        """Returns (changed, new_text)."""
        ...

    # ------------------------------------------------------------------
    # Numeric inputs
    # ------------------------------------------------------------------
    def input_float(
        label: str,
        value: float,
        step: float = 0.0,
        step_fast: float = 0.0,
        format: str = "%.3f",
        flags: imgui.InputTextFlags = ...,
    ) -> Tuple[bool, float]:
        """Returns (changed, new_value)."""
        ...

    def input_int(
        label: str,
        value: int,
        step: int = 1,
        step_fast: int = 100,
        flags: imgui.InputTextFlags = ...,
    ) -> Tuple[bool, int]:
        """Returns (changed, new_value)."""
        ...

    # ------------------------------------------------------------------
    # Sliders
    # ------------------------------------------------------------------
    def slider_float(
        label: str,
        value: float,
        min: float,
        max: float,
        format: str = "%.3f",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, float]:
        """Returns (changed, new_value)."""
        ...

    def slider_int(
        label: str,
        value: int,
        min: int,
        max: int,
        format: str = "%d",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, int]:
        """Returns (changed, new_value)."""
        ...

    # ------------------------------------------------------------------
    # Drag floats
    # ------------------------------------------------------------------
    def drag_float(
        label: str,
        value: float,
        speed: float = 1.0,
        min: float = 0.0,
        max: float = 0.0,
        format: str = "%.3f",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, float]:
        """Returns (changed, new_value)."""
        ...

    def drag_float2(
        label: str,
        value: Tuple[float, float],
        speed: float = 1.0,
        min: float = 0.0,
        max: float = 0.0,
        format: str = "%.3f",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, Tuple[float, float]]:
        """Returns (changed, new_value)."""
        ...

    def drag_float3(
        label: str,
        value: Tuple[float, float, float],
        speed: float = 1.0,
        min: float = 0.0,
        max: float = 0.0,
        format: str = "%.3f",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, Tuple[float, float, float]]:
        """Returns (changed, new_value)."""
        ...

    def drag_float4(
        label: str,
        value: Tuple[float, float, float, float],
        speed: float = 1.0,
        min: float = 0.0,
        max: float = 0.0,
        format: str = "%.3f",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, Tuple[float, float, float, float]]:
        """Returns (changed, new_value)."""
        ...

    # ------------------------------------------------------------------
    # Drag ints
    # ------------------------------------------------------------------
    def drag_int(
        label: str,
        value: int,
        speed: float = 1.0,
        min: int = 0,
        max: int = 0,
        format: str = "%d",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, int]:
        """Returns (changed, new_value)."""
        ...

    def drag_int2(
        label: str,
        value: Tuple[int, int],
        speed: float = 1.0,
        min: int = 0,
        max: int = 0,
        format: str = "%d",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, Tuple[int, int]]:
        """Returns (changed, new_value)."""
        ...

    def drag_int3(
        label: str,
        value: Tuple[int, int, int],
        speed: float = 1.0,
        min: int = 0,
        max: int = 0,
        format: str = "%d",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, Tuple[int, int, int]]:
        """Returns (changed, new_value)."""
        ...

    def drag_int4(
        label: str,
        value: Tuple[int, int, int, int],
        speed: float = 1.0,
        min: int = 0,
        max: int = 0,
        format: str = "%d",
        flags: imgui.SliderFlags = ...,
    ) -> Tuple[bool, Tuple[int, int, int, int]]:
        """Returns (changed, new_value)."""
        ...

    # ------------------------------------------------------------------
    # Combo
    # ------------------------------------------------------------------
    def combo(
        label: str,
        current_item: int,
        items: List[str],
    ) -> Tuple[bool, int]:
        """Returns (changed, new_index)."""
        ...

    # ------------------------------------------------------------------
    # Color pickers / editors
    # ------------------------------------------------------------------
    def color_edit3(
        label: str,
        color: imgui.Vec4,
        flags: imgui.ColorEditFlags = ...,
    ) -> Tuple[bool, imgui.Vec4]:
        """
        Edit RGB. Returns (changed, new_color).
        The alpha component of the returned Vec4 is preserved from the input.
        """
        ...

    def color_edit4(
        label: str,
        color: imgui.Vec4,
        flags: imgui.ColorEditFlags = ...,
    ) -> Tuple[bool, imgui.Vec4]:
        """Returns (changed, new_color) with all four RGBA components."""
        ...

    def color_picker3(
        label: str,
        color: imgui.Vec4,
        flags: imgui.ColorEditFlags = ...,
    ) -> Tuple[bool, imgui.Vec4]:
        """Full-size RGB picker. Returns (changed, new_color)."""
        ...

    def color_picker4(
        label: str,
        color: imgui.Vec4,
        flags: imgui.ColorEditFlags = ...,
    ) -> Tuple[bool, imgui.Vec4]:
        """Full-size RGBA picker. Returns (changed, new_color)."""
        ...

    # ------------------------------------------------------------------
    # Image
    # ------------------------------------------------------------------
    def image(
        texture_id: int,
        image_size: imgui.Vec2,
        uv0: imgui.Vec2 = ...,
        uv1: imgui.Vec2 = ...,
        tint_col: imgui.Vec4 = ...,
        border_col: imgui.Vec4 = ...,
    ) -> None:
        """
        Render a texture.
        uv0/uv1 default to (0,0)/(1,1).
        tint_col defaults to opaque white; border_col defaults to transparent.
        """
        ...

    # ------------------------------------------------------------------
    # Drawing / Viewport
    # ------------------------------------------------------------------
    def get_window_draw_list() -> imgui.DrawList:
        """
        Return the draw list for the current window.
        The returned reference is only valid within the current frame.
        """
        ...

    def get_background_draw_list() -> imgui.DrawList:
        """Draw list rendered behind all windows. Valid for current frame only."""
        ...

    def get_foreground_draw_list() -> imgui.DrawList:
        """Draw list rendered in front of all windows. Valid for current frame only."""
        ...

    def get_main_viewport() -> imgui.Viewport:
        """Return the main viewport. Do not store across frames."""
        ...

    # DrawList standalone functions (operate on an explicit DrawList argument)
    def drawlist_add_line(
        drawlist: imgui.DrawList,
        p1: imgui.Vec2,
        p2: imgui.Vec2,
        col: int,
        thickness: float = 1.0,
    ) -> None: ...

    def drawlist_add_rect(
        drawlist: imgui.DrawList,
        p_min: imgui.Vec2,
        p_max: imgui.Vec2,
        col: int,
        rounding: float = 0.0,
        flags: imgui.DrawFlags = ...,
        thickness: float = 1.0,
    ) -> None: ...

    def drawlist_add_rect_filled(
        drawlist: imgui.DrawList,
        p_min: imgui.Vec2,
        p_max: imgui.Vec2,
        col: int,
        rounding: float = 0.0,
        flags: imgui.DrawFlags = ...,
    ) -> None: ...

    def drawlist_add_circle(
        drawlist: imgui.DrawList,
        center: imgui.Vec2,
        radius: float,
        col: int,
        num_segments: int = 0,
        thickness: float = 1.0,
    ) -> None: ...

    def drawlist_add_circle_filled(
        drawlist: imgui.DrawList,
        center: imgui.Vec2,
        radius: float,
        col: int,
        num_segments: int = 0,
    ) -> None: ...

    def drawlist_add_triangle(
        drawlist: imgui.DrawList,
        p1: imgui.Vec2,
        p2: imgui.Vec2,
        p3: imgui.Vec2,
        col: int,
        thickness: float = 1.0,
    ) -> None: ...

    def drawlist_add_triangle_filled(
        drawlist: imgui.DrawList,
        p1: imgui.Vec2,
        p2: imgui.Vec2,
        p3: imgui.Vec2,
        col: int,
    ) -> None: ...

    def drawlist_add_text(
        drawlist: imgui.DrawList,
        pos: imgui.Vec2,
        col: int,
        text: str,
    ) -> None: ...

    def drawlist_add_image(
        drawlist: imgui.DrawList,
        texture_id: int,
        p_min: imgui.Vec2,
        p_max: imgui.Vec2,
        uv_min: imgui.Vec2 = ...,
        uv_max: imgui.Vec2 = ...,
        col: int = ...,
    ) -> None: ...

    # ------------------------------------------------------------------
    # Text utilities
    # ------------------------------------------------------------------
    def calc_text_size(text: str) -> Tuple[float, float]:
        """Return (width, height) of the given text using the current font."""
        ...

    def get_available_region() -> Tuple[float, float]:
        """Return (width, height) of the remaining content region in the current window."""
        ...

    # ------------------------------------------------------------------
    # Fonts
    # ------------------------------------------------------------------
    def push_font(font: imgui.Font) -> None: ...
    def pop_font() -> None: ...

    def get_font_size() -> float: ...
    def get_font_tex_uv_white_pixel() -> Tuple[float, float]: ...

    # Glyph range helpers (route through current context's font atlas)
    def get_glyph_ranges_default() -> int: ...
    def get_glyph_ranges_greek() -> int: ...
    def get_glyph_ranges_korean() -> int: ...
    def get_glyph_ranges_japanese() -> int: ...
    def get_glyph_ranges_chinese_full() -> int: ...
    def get_glyph_ranges_chinese_simplified_common() -> int: ...
    def get_glyph_ranges_cyrillic() -> int: ...
    def get_glyph_ranges_thai() -> int: ...
    def get_glyph_ranges_vietnamese() -> int: ...

    # ------------------------------------------------------------------
    # Tables
    # ------------------------------------------------------------------
    def begin_table(
        str_id: str,
        column_count: int,
        flags: imgui.TableFlags = ...,
        outer_size: imgui.Vec2 = ...,
        inner_width: float = 0.0,
    ) -> bool: ...

    def end_table() -> None: ...

    def table_next_row(
        row_flags: imgui.TableRowFlags = ...,
        min_row_height: float = 0.0,
    ) -> None: ...

    def table_next_column() -> bool: ...

    def table_set_column_index(column_n: int) -> bool: ...

    def table_setup_column(
        label: str,
        flags: imgui.TableColumnFlags = ...,
        init_width_or_weight: float = 0.0,
        user_id: int = 0,
    ) -> None: ...

    def table_setup_scroll_freeze(cols: int, rows: int) -> None: ...
    def table_headers_row() -> None: ...
    def table_header(label: str) -> None: ...

    def table_get_sort_specs() -> List[Tuple[int, int, int]]:
        """
        Return current sort specs as a list of (column_index, sort_order, sort_direction)
        tuples and clear the SpecsDirty flag.

        sort_direction: 1 = Ascending, 2 = Descending (matches imgui.SortDirection).
        Returns an empty list when there are no specs or the table isn't sortable.
        Only call this when the TableFlags.Sortable flag was set on begin_table().
        """
        ...

    def table_get_column_count() -> int: ...
    def table_get_column_index() -> int: ...
    def table_get_row_index() -> int: ...

    def table_get_column_flags(column_n: int = -1) -> imgui.TableColumnFlags: ...

    def table_set_column_enabled(column_n: int, enabled: bool) -> None: ...

    def table_set_bg_color(
        target: imgui.TableBgTarget,
        color: int,
        column_n: int = -1,
    ) -> None: ...

    # ------------------------------------------------------------------
    # Tree / Collapsing headers
    # ------------------------------------------------------------------
    def tree_node(label: str) -> bool: ...

    def tree_node_ex(
        label: str,
        flags: imgui.TreeNodeFlags = ...,
    ) -> bool: ...

    def tree_pop() -> None: ...
    def tree_push(str_id: str) -> None: ...

    def collapsing_header(
        label: str,
        flags: imgui.TreeNodeFlags = ...,
    ) -> bool: ...

    def set_next_item_open(is_open: bool, cond: imgui.Cond = ...) -> None: ...
    def get_tree_node_to_label_spacing() -> float: ...

    # ------------------------------------------------------------------
    # Menus
    # ------------------------------------------------------------------
    def begin_menu_bar() -> bool: ...
    def end_menu_bar() -> None: ...
    def begin_main_menu_bar() -> bool: ...
    def end_main_menu_bar() -> None: ...

    def begin_menu(label: str, enabled: bool = True) -> bool: ...
    def end_menu() -> None: ...

    def menu_item(
        label: str,
        shortcut: str = "",
        selected: bool = False,
        enabled: bool = True,
    ) -> bool: ...

    # ------------------------------------------------------------------
    # Popups
    # ------------------------------------------------------------------
    def open_popup(str_id: str, flags: imgui.PopupFlags = ...) -> None: ...

    def begin_popup(str_id: str, flags: imgui.WindowFlags = ...) -> bool: ...

    def begin_popup_modal(
        name: str,
        p_open: Optional[bool] = None,
        flags: imgui.WindowFlags = ...,
    ) -> Tuple[bool, Optional[bool]]:
        """
        Begin a modal popup window.
        p_open controls the close button — same semantics as begin().
        Returns (visible, p_open).
        """
        ...

    def end_popup() -> None: ...

    def begin_popup_context_item(
        str_id: str = "",
        flags: imgui.PopupFlags = ...,
    ) -> bool: ...

    def begin_popup_context_window(
        str_id: str = "",
        flags: imgui.PopupFlags = ...,
    ) -> bool: ...

    def begin_popup_context_void(
        str_id: str = "",
        flags: imgui.PopupFlags = ...,
    ) -> bool: ...

    def is_popup_open(str_id: str, flags: imgui.PopupFlags = ...) -> bool: ...

    # ------------------------------------------------------------------
    # Selectables
    # ------------------------------------------------------------------
    def selectable(
        label: str,
        selected: bool = False,
        flags: imgui.SelectableFlags = ...,
        size: imgui.Vec2 = ...,
    ) -> bool: ...

    # ------------------------------------------------------------------
    # Item state queries
    # ------------------------------------------------------------------
    def is_item_hovered(flags: imgui.HoveredFlags = ...) -> bool: ...
    def is_item_active() -> bool: ...
    def is_item_focused() -> bool: ...
    def is_item_clicked(mouse_button: imgui.MouseButton = ...) -> bool: ...
    def is_item_visible() -> bool: ...
    def is_item_edited() -> bool: ...
    def is_item_activated() -> bool: ...
    def is_item_deactivated() -> bool: ...
    def is_item_deactivated_after_edit() -> bool: ...
    def is_item_toggled_open() -> bool: ...

    def get_item_rect_min() -> Tuple[float, float]: ...
    def get_item_rect_max() -> Tuple[float, float]: ...
    def get_item_rect_size() -> Tuple[float, float]: ...

    # ------------------------------------------------------------------
    # Window state queries
    # ------------------------------------------------------------------
    def is_window_focused(flags: imgui.FocusedFlags = ...) -> bool: ...
    def is_window_hovered(flags: imgui.HoveredFlags = ...) -> bool: ...

    # ------------------------------------------------------------------
    # Mouse queries
    # ------------------------------------------------------------------
    def is_mouse_down(button: imgui.MouseButton = ...) -> bool: ...
    def is_mouse_clicked(button: imgui.MouseButton = ..., repeat: bool = False) -> bool: ...
    def is_mouse_released(button: imgui.MouseButton = ...) -> bool: ...
    def is_mouse_double_clicked(button: imgui.MouseButton = ...) -> bool: ...

    def get_mouse_pos() -> Tuple[float, float]: ...
    def get_mouse_delta() -> Tuple[float, float]: ...

    def get_mouse_drag_delta(
        button: imgui.MouseButton = ...,
        lock_threshold: float = -1.0,
    ) -> Tuple[float, float]: ...

    def reset_mouse_drag_delta(button: imgui.MouseButton = ...) -> None: ...

    def is_mouse_hovering_rect(
        min: imgui.Vec2,
        max: imgui.Vec2,
        clip: bool = True,
    ) -> bool: ...

    def is_mouse_pos_valid(pos: Optional[Tuple[float, float]] = None) -> bool:
        """
        Check whether a mouse position is valid (not FLT_MAX sentinel).
        Pass None to check the current frame's mouse position.
        """
        ...

    # ------------------------------------------------------------------
    # Keyboard queries
    # ------------------------------------------------------------------
    def is_key_down(key: imgui.Key) -> bool: ...
    def is_key_pressed(key: imgui.Key, repeat: bool = True) -> bool: ...
    def is_key_released(key: imgui.Key) -> bool: ...

    def get_key_pressed_amount(
        key: imgui.Key,
        repeat_delay: float,
        rate: float,
    ) -> int: ...

    def set_keyboard_focus_here(offset: int = 0) -> None: ...

    # ------------------------------------------------------------------
    # Misc utilities
    # ------------------------------------------------------------------
    def get_time() -> float: ...
    def get_frame_count() -> int: ...
    def get_frame_height() -> float: ...
    def get_frame_height_with_spacing() -> float: ...

    def get_display_size() -> Tuple[float, float]: ...
    def get_display_framebuffer_scale() -> Tuple[float, float]: ...

    def get_cursor_pos() -> Tuple[float, float]: ...
    def get_cursor_start_pos() -> Tuple[float, float]: ...
    def get_cursor_screen_pos() -> Tuple[float, float]: ...

    def get_text_line_height() -> float: ...
    def get_text_line_height_with_spacing() -> float: ...

    def get_color_u32(col: imgui.Vec4) -> int: ...
    def get_color_u32_indexed(idx: imgui.Col, alpha_mul: float = 1.0) -> int: ...

    def get_style() -> imgui.Style:
        """Return a reference to the global ImGuiStyle. Do not store long-term."""
        ...

    def get_io() -> imgui.IO:
        """Return a reference to the global ImGuiIO. Do not store long-term."""
        ...

    # ------------------------------------------------------------------
    # Clipboard
    # ------------------------------------------------------------------
    def get_clipboard_text() -> str: ...
    def set_clipboard_text(text: str) -> None: ...


class CursorMode:

    Normal: int
    Hidden: int
    Disabled: int

class Window:

    def __init__(self, width: int, height: int, title: str = "GLUX", gl_major: int = 3, gl_minor: int = 3, vsync: bool = True, y_up: bool = True) -> Window: ...
    def run(self) -> None: ...
    def get_size(self) -> Tuple[int, int]: ...
    def get_framebuffer_size(self) -> Tuple[int, int]: ...
    def get_position(self) -> Tuple[int, int]: ...
    def get_title(self) -> str: ...
    def is_y_up(self) -> bool: ...
    def is_vsync(self) -> bool: ...
    def is_fullscreen(self) -> bool: ...
    def should_close(self) -> bool: ...
    def screenshot(self, flip_vertically: bool) -> bytes: ...
    def set_size(self, width: int, height: int) -> None: ...
    def set_title(self, title: str) -> None: ...
    def set_vsync(self, vsync: bool) -> None: ...
    def set_y_up(self, y_up: bool) -> None: ...
    def set_position(self, x: int, y: int) -> None: ...
    def set_fullscreen(self, fullscreen: bool) -> None: ...
    def set_opacity(self, alpha: float) -> None: ...
    def set_resizable(self, resizable: bool) -> None: ...
    def set_decorated(self, decorated: bool) -> None: ...
    def set_floating(self, floating: bool) -> None: ...
    def set_icon(self, data: bytes, width: int, height: int) -> None: ...
    def close(self) -> None: ...
    def set_events_callback(self, callback: Callable[[], None]) -> None: ...
    def set_process_callback(self, callback: Callable[[], None]) -> None: ...
    def set_render_callback(self, callback: Callable[[], None]) -> None: ...
    def set_render_ui_callback(self, callback: Callable[[], None]) -> None: ...

class Keyboard:

    key: int
    scancode: int
    action: int
    mods: int
    def held(self, key: int) -> bool: ...

keyboard: Keyboard

class Mouse:

    button: int
    action: int
    mod: int
    xoffset : int
    yoffset : int
    def held(self, button: int) -> bool: ...

mouse: Mouse

class Cursor:

    x: float
    y: float
    def set_mode(self, mode: any) -> None: ...
    def set_visible(self, visible: bool) -> None: ...
    def set_pos(self, x: float, y: float) -> None: ...

cursor: Cursor

class mods:

    SHIFT: int
    CONTROL: int
    ALT: int
    SUPER: int
    CAPS_LOCK: int
    NUM_LOCK: int

class actions:

    PRESS: int
    RELEASE: int
    REPEAT: int

class scancodes:

    KEY_UNKNOWN: int

class keys:

    K_SPACE: int
    K_APOSTROPHE: int
    K_COMMA: int
    K_MINUS: int
    K_PERIOD: int
    K_SLASH: int
    K_0: int
    K_1: int
    K_2: int
    K_3: int
    K_4: int
    K_5: int
    K_6: int
    K_7: int
    K_8: int
    K_9: int
    K_SEMICOLON: int
    K_EQUAL: int
    K_A: int
    K_B: int
    K_C: int
    K_D: int
    K_E: int
    K_F: int
    K_G: int
    K_H: int
    K_I: int
    K_J: int
    K_K: int
    K_L: int
    K_M: int
    K_N: int
    K_O: int
    K_P: int
    K_Q: int
    K_R: int
    K_S: int
    K_T: int
    K_U: int
    K_V: int
    K_W: int
    K_X: int
    K_Y: int
    K_Z: int
    K_LEFT_BRACKET: int
    K_BACKSLASH: int
    K_RIGHT_BRACKET: int
    K_GRAVE_ACCENT: int
    K_WORLD_1: int
    K_WORLD_2: int
    K_ESCAPE: int
    K_ENTER: int
    K_TAB: int
    K_BACKSPACE: int
    K_INSERT: int
    K_DELETE: int
    K_RIGHT: int
    K_LEFT: int
    K_DOWN: int
    K_UP: int
    K_PAGE_UP: int
    K_PAGE_DOWN: int
    K_HOME: int
    K_END: int
    K_CAPS_LOCK: int
    K_SCROLL_LOCK: int
    K_NUM_LOCK: int
    K_PRINT_SCREEN: int
    K_PAUSE: int
    K_F1: int
    K_F2: int
    K_F3: int
    K_F4: int
    K_F5: int
    K_F6: int
    K_F7: int
    K_F8: int
    K_F9: int
    K_F10: int
    K_F11: int
    K_F12: int
    K_F13: int
    K_F14: int
    K_F15: int
    K_F16: int
    K_F17: int
    K_F18: int
    K_F19: int
    K_F20: int
    K_F21: int
    K_F22: int
    K_F23: int
    K_F24: int
    K_F25: int
    K_KP_0: int
    K_KP_1: int
    K_KP_2: int
    K_KP_3: int
    K_KP_4: int
    K_KP_5: int
    K_KP_6: int
    K_KP_7: int
    K_KP_8: int
    K_KP_9: int
    K_KP_DECIMAL: int
    K_KP_DIVIDE: int
    K_KP_MULTIPLY: int
    K_KP_SUBTRACT: int
    K_KP_ADD: int
    K_KP_ENTER: int
    K_KP_EQUAL: int
    K_LEFT_SHIFT: int
    K_LEFT_CONTROL: int
    K_LEFT_ALT: int
    K_LEFT_SUPER: int
    K_RIGHT_SHIFT: int
    K_RIGHT_CONTROL: int
    K_RIGHT_ALT: int
    K_RIGHT_SUPER: int
    K_MENU: int

class buttons:

    M_1: int
    M_2: int
    M_3: int
    M_4: int
    M_5: int
    M_6: int
    M_7: int
    M_8: int
    M_LEFT: int
    M_RIGHT: int
    M_MIDDLE: int