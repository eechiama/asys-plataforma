function callback_Popup_EA(hObj, event)

hs = guidata(hObj);
info = getappdata(hs.Figure,'info');

aux = get(hs.Popup_EA,'string');
val = get(hs.Popup_EA,'value');

info.EAToSet = aux{val};

setappdata(hs.Figure,'info',info);
guidata(hObj,hs);

end
