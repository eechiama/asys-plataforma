function callback_toggle_adc(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
muestras = getappdata(hs.Figure,'muestras');

if info.SerialOpened == 0
    errordlg('No hay ningún puerto abierto.');
    return;
end

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
        fprintf(hs.Serial,'$M1#');
        msgbox('Sampling Started.');
        
        % actualizo el flag
        info.Sampling = 1;
        
        % Cambio la string del boton a 'Stop'
        set(hs.Toggle_StartStop,'string','Stop Sampling');
        
    % si está activo, stop
    case 1
        % detengo el muestreo
        fprintf(hs.Serial,'$M0#');
        msgbox('Sampling Stopped');
        
        % actualizo el flag
        info.Sampling = 0;
        
        % Cambio la string del boton a 'Start'
        set(hs.Toggle_StartStop,'string','Start Sampling');
end

setappdata(hs.Figure,'info',info);
setappdata(hs.Figure,'muestras',muestras);
guidata(hObj.Parent,hs);

end
