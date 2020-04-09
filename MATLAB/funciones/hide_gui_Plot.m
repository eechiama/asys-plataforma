% hide all plot stuff, both platforms
function hide_gui_Plot(hObj)
    hs = guidata(hObj.Parent);
    
    set(hs.strSave,'visible','off');
    set(hs.Edit_File,'visible','off');
    
    set(hs.Push_Save,'visible','off');
    set(hs.Toggle_StartStop,'visible','off');
    set(hs.Toggle_pwm,'visible','off');
    
    set(hs.strPlotConfig,'visible','off');
    
    set(hs.strXlim,'visible','off');
    set(hs.Edit_Xlim1,'visible','off');
    set(hs.Text_Xlim_Guion,'visible','off');
    set(hs.Edit_Xlim2,'visible','off');
    
    set(hs.strYlim,'visible','off');
    set(hs.Edit_Ylim1,'visible','off');
    set(hs.Text_Ylim_Guion,'visible','off');
    set(hs.Edit_Ylim2,'visible','off');
    
    set(hs.Checkbox_RTP,'visible','off');
    set(hs.Checkbox_Tight,'visible','off');
    set(hs.Checkbox_Grid,'visible','off');
    
    set(hs.plotPanel,'visible','off');
    set(hs.Axis,'visible','off');
    set(hs.Push_UpdatePlot,'visible','off');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end