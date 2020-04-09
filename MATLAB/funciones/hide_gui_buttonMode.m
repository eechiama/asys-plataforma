% hide all buttonMode stuff, both platforms
function hide_gui_buttonMode(hObj)
    hs = guidata(hObj.Parent);
    
    % infotronic
    set(hs.strButtons_NoInfotronic,'visible','off');
    
    % arduino
    set(hs.Toggle_Buttons,'visible','off');
    set(hs.Popup_waveform_Buttons,'visible','off');
    
    % shared objects with generator app for arduino
    set(hs.strSignal,'visible','off');
    set(hs.strFreqDiv,'visible','off');
    set(hs.Popup_fdiv,'visible','off');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end