function callback_Popup_fdiv(hObj, event)

hs = guidata(hObj.Parent);
modeGEN = getappdata(hs.Figure,'modeGEN');

% Obtengo el el dato del popup
aux = get(hs.Popup_fdiv,'string');
val = get(hs.Popup_fdiv,'value');

% Actualizo el divisor a enviar al generador
modeGEN.divider = aux{val};

setappdata(hs.Figure,'modeGEN',modeGEN);
guidata(hObj.Parent, hs);
end