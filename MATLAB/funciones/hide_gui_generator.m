% hide all generator stuff, both platforms
function hide_gui_generator(hObj)
    hs = guidata(hObj.Parent); 
    
    % infotronic
    set(hs.str_pwm_NoInfotronic,'visible','off');
    
    % arduino
    set(hs.strSignal,'visible','off');
    set(hs.Popup_waveform,'visible','off');
    
    set(hs.strFreqDiv,'visible','off');
    set(hs.Popup_fdiv,'visible','off');
    
    % LPC845
    set(hs.Popup_waveform_LPC845,'visible','off');
    set(hs.Popup_fdiv_LPC845,'visible','off');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end