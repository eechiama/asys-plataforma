% show all ADC stuff, according to platform
function show_gui_generator(hObj, platform)
    hs = guidata(hObj.Parent);
    
    % case: platform == infotronic
    if( platform == hs.RadioBut_Infotronic )
        set(hs.str_pwm_NoInfotronic,'visible','on');
    end
    
    % case: platform == arduino
    if( platform == hs.RadioBut_Arduino )
        set(hs.strSignal,'visible','on');
        set(hs.Popup_waveform,'visible','on');

        set(hs.strFreqDiv,'visible','on');
        set(hs.Popup_fdiv,'visible','on');
    end
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end