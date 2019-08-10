function callback_Popup_Fs(hObj, event)

    hs = guidata(hObj.Parent);
    info = getappdata(hs.Figure,'info');

    % Obtengo el el dato del popup
    aux = get(hs.Popup_Fs,'string');
    val = get(hs.Popup_Fs,'value');
    
    % Actualizo el string FsToSet
    info.FsToSet = aux{val};
    setappdata(hs.Figure,'info',info);    
    
    guidata(hObj.Parent, hs);
    
end

% Este callback actualiza el valor FsToSet.