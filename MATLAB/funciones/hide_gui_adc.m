% hide all ADC stuff, both platforms
function hide_gui_adc(hObj)
    hs = guidata(hObj.Parent);
    
    set(hs.strConfigActual,'visible','off');
    set(hs.strDisplayConfig,'visible','off');
    set(hs.strDisplayConfig_ARDUINO,'visible','off');
    set(hs.strDisplayConfig_LPC845,'visible','off');
    
    set(hs.strEntrada,'visible','off');
    set(hs.Popup_EA,'visible','off');
    set(hs.Popup_EA_LPC845,'visible','off');
    set(hs.Push_Config_EA,'visible','off');
    set(hs.strNoArduinoConfig2,'visible','off');
    
    set(hs.strFsToSet,'visible','off');
    set(hs.Popup_Fs,'visible','off');
    set(hs.Push_Config_Fs,'visible','off');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end