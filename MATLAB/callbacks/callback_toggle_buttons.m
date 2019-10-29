function callback_toggle_buttons(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
muestras = getappdata(hs.Figure,'muestras');
modeBUTTONS = getappdata(hs.Figure,'modeBUTTONS');
modeGEN = getappdata(hs.Figure,'modeGEN');

if info.SerialOpened == 0
    errordlg('No hay ningún puerto abierto.');
    return;
end

% construyo el comando a enviar
% identifico la señal a pedirle al generador

if strcmp(modeBUTTONS.signal, 'senoidal 500hz')
    waveform = 'S';    
end

if strcmp(modeBUTTONS.signal, 'rampa 245hz')
    waveform = 'R';    
end

if strcmp(modeBUTTONS.signal, 'cuadrada 500hz')
    waveform = 'Q';
end

if strcmp(modeBUTTONS.signal, 'impulso 500hz')
    waveform = 'I';    
end

% comando
button_command = '$B1,';
button_command = strcat(button_command, waveform);
button_command = strcat(button_command, ',');
button_command = strcat(button_command, modeGEN.divider);
button_command = strcat(button_command,'.#');

switch info.Sampling
    
    % si está inactivo
    case 0
        
        % Vacío el input buffer del serial
        flushinput(hs.Serial);
        % Vacío el vector de datos muestreados
        muestras=[];
        % Clear al plot
        reset_plot(hs);
        % indico que debe hacerse el primer plot
        info.FirstPlot = 1;
        
        % hacer start
        fprintf(hs.Serial, button_command);
        msgbox('Buttons Enabled.');
        
        % actualizo el flag
        info.Sampling = 1;
        
        % Cambio la string del boton a 'Stop'
        set(hs.Toggle_Buttons,'string','Disable');
        
    % si está activo, stop
    case 1
        % deshabilito el modo botones en el micro
        fprintf(hs.Serial,'$B0#');
        msgbox('Buttons Disabled');
        
        % actualizo el flag
        info.Sampling = 0;
        
        % Cambio la string del boton a 'Start'
        set(hs.Toggle_Buttons,'string','Enable');
end

setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'muestras',muestras);
guidata(hObj.Parent,hs);
end
