% show all Plot stuff
function show_gui_plot(hObj, platform)
    hs = guidata(hObj.Parent);
    
    set(hs.strSave,'visible','on');
    set(hs.Edit_File,'visible','on');
    
    % push buttons
    set(hs.Push_Save,'visible','on');
    set(hs.Toggle_StartStop,'visible','on');
    if( (platform == hs.RadioBut_Arduino) || (platform == hs.RadioBut_LPC845))
        set(hs.Toggle_pwm,'visible','on');
    end
    set(hs.Push_TestSig,'visible','on');
    
    set(hs.strPlotConfig,'visible','on');
    
    set(hs.strXlim,'visible','on');
    set(hs.Edit_Xlim1,'visible','on');
    set(hs.Text_Xlim_Guion,'visible','on');
    set(hs.Edit_Xlim2,'visible','on');
    
    set(hs.strYlim,'visible','on');
    set(hs.Edit_Ylim1,'visible','on');
    set(hs.Text_Ylim_Guion,'visible','on');
    set(hs.Edit_Ylim2,'visible','on');
    
    set(hs.Checkbox_Tight,'visible','on');
    
    set(hs.plotPanel,'visible','on');
    set(hs.Axis,'visible','on');
    set(hs.Push_UpdatePlot,'visible','on');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end