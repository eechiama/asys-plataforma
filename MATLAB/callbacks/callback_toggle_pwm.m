function callback_toggle_pwm(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeGEN = getappdata(hs.Figure,'modeGEN');

if info.SerialOpened == 0
    errordlg('No hay ningún puerto abierto.');
    return;
end

% plataforma actual?
plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

%% Según plataforma seleccionada, identifico código de waveform a enviar

if plataforma == hs.RadioBut_Arduino
    aux_gen = modeGEN.arduino;
    aux_str_list = get(hs.Popup_waveform,'string');
    aux_waveform_codes = {'R', 'H', 'S', 'Q', 'E', 'I'};
end

if plataforma == hs.RadioBut_LPC845
    aux_gen = modeGEN.LPC845;
    aux_str_list = get(hs.Popup_waveform_LPC845,'string');
    aux_waveform_codes = {'S', 'R', 'Q'};
end

for idx=1:length(aux_str_list)
    if( strcmp(aux_gen.signal, aux_str_list(idx)) )
        waveform = aux_waveform_codes(idx);
        break;
    end
end

%% construyo el comando a enviar (en caso de start)

% comando
pwm_command = '$P1,';
pwm_command = strcat(pwm_command, waveform);
pwm_command = strcat(pwm_command, ',');
pwm_command = strcat(pwm_command, aux_gen.divider);
pwm_command = strcat(pwm_command,'.#');
pwm_command = char(pwm_command);

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