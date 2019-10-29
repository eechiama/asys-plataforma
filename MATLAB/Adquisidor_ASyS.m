%% ASyS - Adquisidor con Placa de Info II

% Estrategia para manejar datos entra:
% --> guidata() para intercambiar la estructura de handles
% --> setappdata() y getappdata() para manejar otros datos.

%% Inicialización

clc;
clear;

addpath('callbacks')
addpath('funciones')

muestras=[];

% Mode ADC
% Frequency
modeADC.FsToSet = '2500';
modeADC.FsActual = '2500';
modeADC.FsActual_ARDUINO = '2500';
% Input
modeADC.EAActual = '2';
modeADC.EAToSet = 'EA2';

% Mode Generator
modeGEN.signal = 'rampa 245hz'; % default
modeGEN.divider = '1';

% Modo Botones
modeBUTTONS.signal = 'senoidal 500hz';

% gui status flags
info.SerialOpened = 0;
info.Sampling = 0;
info.TestSignal = 0;
info.Generator = 0;

% plot information
info.FirstPlot = 1;
% plot config
info.MedianaSize = 1;
info.InputBufferBytes = 0;
info.SamplesToRead_M3 = ( str2double(modeADC.FsActual) / info.MedianaSize ) / 5;
info.SamplesToRead_ARDUINO = ( str2double(modeADC.FsActual_ARDUINO) / info.MedianaSize ) / 5;
info.SamplesToRead = info.SamplesToRead_M3; % default es el cortex

% Save the data
hs = Gui_Start();
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
            if get(hs.Checkbox_RTP, 'value') == 1
                plot_tiempo_real(hs);
            end
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
