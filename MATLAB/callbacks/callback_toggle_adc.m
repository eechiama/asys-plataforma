function callback_toggle_adc(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');
muestras = getappdata(hs.Figure,'muestras');

% plataforma actual?
plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

%% protección contra puerto serie no abierto
if info.SerialOpened == 0
    errordlg('No hay ningún puerto abierto.');
    return;
end

%% Según plataforma seleccionada, configuro Fs a utilizar en fuciones de plot

if plataforma == hs.RadioBut_LPC1769
    info.plotFs = str2double(modeADC.LPC1769.Fs) / info.MedianaSize;
end

if plataforma == hs.RadioBut_Arduino
    info.plotFs = str2double(modeADC.Arduino.Fs) / info.MedianaSize;
end

if plataforma == hs.RadioBut_LPC845
    info.plotFs = str2double(modeADC.LPC845.Fs) / info.MedianaSize;
end

%% Según estado previo de sampling, comienzo o detengo
switch info.Sampling
    
    % si no estaba sampleando
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
        fprintf(hs.Serial,'$M1#');
        msgbox('Sampling Started.');
        
        % actualizo el flag
        info.Sampling = 1;
        
        % Cambio la string del boton a 'Stop'
        set(hs.Toggle_StartStop,'string','Stop ADC');
        
    % si está activo, stop
    case 1
        % detengo el muestreo
        fprintf(hs.Serial,'$M0#');
        msgbox('Sampling Stopped');
        
        % actualizo el flag
        info.Sampling = 0;
        
        % Cambio la string del boton a 'Start'
        set(hs.Toggle_StartStop,'string','Start ADC');
end

setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'muestras',muestras);
guidata(hObj.Parent,hs);

end
