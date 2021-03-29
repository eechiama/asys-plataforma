function callback_Popup_EA(hObj, event)

hs = guidata(hObj);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');

aux = get(hs.Popup_EA,'string');
val = get(hs.Popup_EA,'value');

modeADC.LPC1769.EA_to_set = aux{val};

setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'modeADC',modeADC);
guidata(hObj,hs);

end
