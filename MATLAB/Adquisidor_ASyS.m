%% ASyS - Adquisidor con Placa de Info II

% Estrategia para manejar datos entre scopes:
% --> guidata() para intercambiar la estructura de handles
% --> setappdata() y getappdata() para manejar otros datos.

% Estructuras de datos
% =====================
%
% modeADC:  contiene información de la configuración del ADC
%           (fs y entrada)
%
% modeGEN:  análogo generador PWM
%
% info:     información sobre interfaz gráfica y uso del usuario
%           y settings necesarios para plottear y recibir datos por puerto
%           serie
%
% uiInfo    información sobre TABS y selección activa
%           (inicializada en función gui_start() )

%% Inicialización

clc;
clear;

addpath('callbacks');
addpath('funciones');

muestras=[];

% Mode ADC
% Frequency
modeADC.LPC1769.Fs = '2500';
modeADC.LPC1769.Fs_to_set = '2500';
modeADC.Arduino.Fs = '2500';
modeADC.Arduino.Fs_to_set = '2500';
modeADC.LPC845.Fs = '2500';
modeADC.LPC845.Fs_to_set = '2500';
% Input Infotronic v1
modeADC.LPC1769.EA_infotronic = '2';
modeADC.LPC1769.EA_to_set = 'EA2';
% Input LPC845
modeADC.LPC845.channel = '0';
modeADC.LPC845.channel_to_set = 'Pote';

% Mode Generator
modeGEN.arduino.signal = 'rampa 245hz';
modeGEN.arduino.divider = '1';
modeGEN.LPC845.signal = 'senoidal'; % default LPC845
modeGEN.LPC845.divider = '1';



% Modo Botones
modeBUTTONS.signal = 'senoidal 500hz';

% GUI status flags
info.SerialOpened = 0;
info.Sampling = 0;
info.TestSignal = 0;
info.Generator = 0;

% Information to plot
info.FirstPlot = 1;
info.MedianaSize = 1;
info.plotFs = str2double(modeADC.LPC1769.Fs) / info.MedianaSize; % default es el LPC1769

% Information to retrieve data from serial port
info.InputBufferBytes = 0;
info.SamplesToRead_LPC1769 = ( str2double(modeADC.LPC1769.Fs) / info.MedianaSize ) / 5;
info.SamplesToRead_ARDUINO = ( str2double(modeADC.Arduino.Fs) / info.MedianaSize ) / 5;
info.SamplesToRead_LPC845 = ( str2double(modeADC.LPC845.Fs) / info.MedianaSize ) / 5;
info.SamplesToRead = info.SamplesToRead_LPC1769; % default es el LPC1769

% Save the data
hs = guiStart();
setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'modeADC',modeADC);
setappdata(hs.Figure,'modeGEN',modeGEN);
setappdata(hs.Figure,'modeBUTTONS',modeBUTTONS);
setappdata(hs.Figure,'muestras',muestras);
guidata(hs.Figure,hs);

%% Comienza

while 1
    % Actualizo datos
    drawnow;
    hs = guidata(hs.Figure);
    info = getappdata(hs.Figure,'info');
    muestras = getappdata(hs.Figure,'muestras');
    
    if info.SerialOpened == 1
        info.InputBufferBytes = get(hs.Serial,'bytesavailable');
    end
    
    if info.Sampling == 1
        % Convierto bytes a cantidad de samples
        InputBufferSamples = fix(info.InputBufferBytes/4);
        
        % Adquiero las muestras
        if  InputBufferSamples >= info.SamplesToRead
            new_datos = GetSamples(hs.Serial, info.SamplesToRead );
            muestras = [muestras new_datos];
            setappdata(hs.Figure,'muestras',muestras);
            plot_tiempo_real(hs);
        end
        
    end
    
    if info.TestSignal == 1
        % Convierto bytes a cantidad de samples
        InputBufferSamples = fix(info.InputBufferBytes/3);
        
        % Adquiero las muestras
        if InputBufferSamples >= 85
            signal = GetTestSignal(hs.Serial);
            info.TestSignal = 0;
            setappdata(hs.Figure, 'info', info);
            
            axes(hs.Axis);
            x=1:85;
            plot(x,signal,'b','linewidth',1);
            axis('tight'); grid ('on');
            title('Test Signal','fontsize',15);
            xlabel('muestras');
        end
    end
    
end
