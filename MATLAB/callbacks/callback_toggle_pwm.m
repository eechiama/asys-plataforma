function callback_toggle_pwm(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeGEN = getappdata(hs.Figure,'modeGEN');

if info.SerialOpened == 0
    errordlg('No hay ningún puerto abierto.');
    return;
end

%% en caso de start, construyo el comando a enviar

% identifico la señal a pedirle al generador
if strcmp(modeGEN.signal, 'rampa 245hz')
    waveform = 'R';    
end

if strcmp(modeGEN.signal, 'logic high')
    waveform = 'H';
end
    
if strcmp(modeGEN.signal, 'senoidal 500hz')
    waveform = 'S';    
end

if strcmp(modeGEN.signal, 'cuadrada 500hz')
    waveform = 'Q';
end

if strcmp(modeGEN.signal, 'ECG2')
    waveform = 'E';    
end

if strcmp(modeGEN.signal, 'impulso 500hz')
    waveform = 'I';    
end

% comando
pwm_command = '$P1,';
pwm_command = strcat(pwm_command, waveform);
pwm_command = strcat(pwm_command, ',');
pwm_command = strcat(pwm_command, modeGEN.divider);
pwm_command = strcat(pwm_command,'.#');

%% envío el comando
switch info.Generator

    % si está inactivo
    case 0
        % hacer start
        fprintf(hs.Serial, pwm_command);
        msgbox('PWM comenzado.');
        
        % actualizo el flag
        info.Generator = 1;
        
        % Cambio la string del boton a 'Stop'
        set(hs.Toggle_pwm,'string','Stop PWM');
        
    % si está activo, stop
    case 1
        % detengo el muestreo
        fprintf(hs.Serial,'$P0#');
        msgbox('PWM terminado.');
        
        % actualizo el flag
        info.Generator = 0;
        
        % Cambio la string del boton a 'Start'
        set(hs.Toggle_pwm,'string','Start PWM');
end

setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'modeGEN',modeGEN);
guidata(hObj.Parent,hs);

end