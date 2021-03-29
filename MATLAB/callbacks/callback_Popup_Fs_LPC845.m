function callback_Popup_Fs_LPC845(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');

% Obtengo el el dato del popup
aux = get(hs.Popup_Fs_LPC845,'string');
val = get(hs.Popup_Fs_LPC845,'value');

% Actualizo el string FsToSet
modeADC.LPC845.Fs_to_set = aux{val};

setappdata(hs.Figure,'info',info);    
setappdata(hs.Figure,'modeADC',modeADC);
guidata(hObj.Parent, hs);
    
end