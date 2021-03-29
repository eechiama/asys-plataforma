function callback_Popup_EA_LPC845(hObj, event)

hs = guidata(hObj);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');

aux = get(hs.Popup_EA_LPC845,'string');
val = get(hs.Popup_EA_LPC845,'value');

modeADC.LPC845.channel_to_set = aux{val};

setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'modeADC',modeADC);
guidata(hObj,hs);

end