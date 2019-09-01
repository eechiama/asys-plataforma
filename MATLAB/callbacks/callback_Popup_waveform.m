function callback_Popup_waveform(hObj, event)

hs = guidata(hObj.Parent);
modeGEN = getappdata(hs.Figure,'modeGEN');

% Obtengo el dato del popup
aux = get(hs.Popup_waveform,'string');
val = get(hs.Popup_waveform,'value');

% Actualizo la señal a pedirle al generador
modeGEN.signal = aux{val};

setappdata(hs.Figure,'modeGEN',modeGEN);
guidata(hObj.Parent, hs);
end