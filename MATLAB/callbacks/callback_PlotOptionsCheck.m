function callback_PlotOptionsCheck(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% leo estado de checkboxes
axisTight = get(hs.Checkbox_Tight,'value');

if axisTight == 1
    set(hs.Edit_Xlim1,'Enable','off');
    set(hs.Edit_Xlim2,'Enable','off');
    set(hs.Edit_Ylim1,'Enable','off');
    set(hs.Edit_Ylim2,'Enable','off');
    set(hs.Push_UpdatePlot,'Enable','off');
end

if axisTight == 0
    set(hs.Edit_Xlim1,'Enable','on');
    set(hs.Edit_Xlim2,'Enable','on');
    set(hs.Edit_Ylim1,'Enable','on');
    set(hs.Edit_Ylim2,'Enable','on');
    set(hs.Push_UpdatePlot,'Enable','on');
end

% Guardo los cambios a la variable de la figura
setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);

end