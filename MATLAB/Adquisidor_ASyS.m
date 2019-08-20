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

info.MedianaSize = 1;

info.SerialOpened = 0;
info.Sampling = 0;
info.TestSignal = 0;

info.FsToSet = '2500';
info.FsActual = '2500';
info.FsActual_ARDUINO = '2500';

info.EAActual = '2';
info.EAToSet = 'EA2';

info.FirstPlot = 1;

info.InputBufferBytes = 0;
info.SamplesToRead_M3 = ( str2double(info.FsActual) / info.MedianaSize ) / 5;
info.SamplesToRead_ARDUINO = ( str2double(info.FsActual_ARDUINO) / info.MedianaSize ) / 5;

info.SamplesToRead = info.SamplesToRead_M3; % default es el cortex

hs = Gui_Start();
setappdata(hs.Figure,'info',info);
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