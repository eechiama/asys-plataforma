function callback_PlotOptionsCheck(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% leo estado de checkboxes
rtp = get(hs.Checkbox_RTP,'value');
axisTight = get(hs.Checkbox_Tight,'value');

% para plot en tiempo real, con axis tight: deshabilito xlim, ylim y el botón de re-plot
if rtp == 1 && axisTight == 1
    set(hs.Edit_Xlim1,'Enable','off');
    set(hs.Edit_Xlim2,'Enable','off');
    set(hs.Edit_Ylim1,'Enable','off');
    set(hs.Edit_Ylim2,'Enable','off');
    set(hs.Push_UpdatePlot,'Enable','off');
end

% para plot en tiempo real, sin axis tight: deshabilito xlim y el botón de re-plot
if rtp == 1 && axisTight == 0
    set(hs.Edit_Xlim1,'Enable','off');
    set(hs.Edit_Xlim2,'Enable','off');
    set(hs.Push_UpdatePlot,'Enable','off');
    
    set(hs.Edit_Ylim1,'Enable','on');
    set(hs.Edit_Ylim2,'Enable','on');
end

% para plot manual, sin axis tight: todo habilitado
if rtp == 0 && axisTight == 0
    set(hs.Edit_Xlim1,'Enable','on');
    set(hs.Edit_Xlim2,'Enable','on');
    set(hs.Edit_Ylim1,'Enable','on');
    set(hs.Edit_Ylim2,'Enable','on');
    set(hs.Push_UpdatePlot,'Enable','on');
end

% para plot manual, con axis tight: deshabilito xlim e ylim
if rtp == 0 && axisTight == 1
    set(hs.Edit_Xlim1,'Enable','off');
    set(hs.Edit_Xlim2,'Enable','off');
    set(hs.Edit_Ylim1,'Enable','off');
    set(hs.Edit_Ylim2,'Enable','off');
    set(hs.Push_UpdatePlot,'Enable','on');
end

% Guardo los cambios a la variable de la figura
setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);

end