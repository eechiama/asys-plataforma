function callback_Popup_waveform_LPC845(hObj, event)

hs = guidata(hObj.Parent);
modeGEN = getappdata(hs.Figure,'modeGEN');

% Obtengo el dato del popup
aux = get(hs.Popup_waveform_LPC845,'string');
val = get(hs.Popup_waveform_LPC845,'value');

% Actualizo la señal a pedirle al generador
modeGEN.LPC845.signal = aux{val};

setappdata(hs.Figure,'modeGEN',modeGEN);
guidata(hObj.Parent, hs);
end