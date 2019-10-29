function callback_Popup_waveform_Buttons(hObj, event)

hs = guidata(hObj.Parent);
modeBUTTONS = getappdata(hs.Figure,'modeBUTTONS');

% Obtengo el dato del popup
aux = get(hs.Popup_waveform_Buttons,'string');
val = get(hs.Popup_waveform_Buttons,'value');

% Actualizo la señal a pedirle al generador
modeBUTTONS.signal = aux{val};

setappdata(hs.Figure,'modeBUTTONS',modeBUTTONS);
guidata(hObj.Parent, hs);
end