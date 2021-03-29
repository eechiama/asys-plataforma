function callback_Popup_fdiv(hObj, event)

hs = guidata(hObj.Parent);
modeGEN = getappdata(hs.Figure,'modeGEN');

% Obtengo el el dato del popup
aux = get(hs.Popup_fdiv_LPC845,'string');
val = get(hs.Popup_fdiv_LPC845,'value');

% Actualizo el divisor a enviar al generador
modeGEN.LPC845.divider = aux{val};

setappdata(hs.Figure,'modeGEN',modeGEN);
guidata(hObj.Parent, hs);
end