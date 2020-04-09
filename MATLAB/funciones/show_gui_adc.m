% show all ADC stuff, according to platform
function show_gui_adc(hObj, platform)
    hs = guidata(hObj.Parent);
    
    set(hs.strConfigActual,'visible','on');
    
    set(hs.strFsToSet,'visible','on');
    set(hs.Popup_Fs,'visible','on');
    set(hs.Push_Config_Fs,'visible','on');
    
    % case: platform == infotronic
    if( platform == hs.RadioBut_Infotronic )
        set(hs.strDisplayConfig,'visible','on');
        set(hs.strEntrada,'visible','on');
        set(hs.Popup_EA,'visible','on');
        set(hs.Push_Config_EA,'visible','on');
    end
   
    % case: platform == arduino
    if( platform == hs.RadioBut_Arduino )
        set(hs.strDisplayConfig_ARDUINO,'visible','on');
        set(hs.strNoArduinoConfig2,'visible','on');
    end
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end