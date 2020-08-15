% esta función es similar a callback_update_plot
% Pero esta se llama constantemente desde el súper lazo, si usa tiempo real

function plot_tiempo_real(hs)

INTERVALO = 5;  % variable para agrandar el eje de tiempo, segundos

info = getappdata(hs.Figure,'info');
muestras = getappdata(hs.Figure,'muestras');

ll = length(muestras);
Fs = info.plotFs;

if ll == 0
    errordlg('No hay muestras para graficar.');
    return;
end

dt = 1/Fs;
t = 0 : dt : (ll-1)*dt;

axes(hs.Axis);

hs.Plot = plot(t,muestras,'b','linewidth',1);
grid on;

%% Chequeo límites de los ejes

val = get(hs.Checkbox_Tight,'value');

if val == 1
    axis 'tight';
end

if val == 0
    % consulto el valor actual de xlim
    currentXlims = xlim;

    % si mis muestras exceden el eje de tiempo actual
    if length(t) >= currentXlims(2) / dt
        xlim1 = currentXlims(2) ;
        xlim2 = INTERVALO + xlim1 ;
        xlim([xlim1 xlim2]);
    end
    
    % leo la configuración de ylim requerida
    ylim1 = get(hs.Edit_Ylim1,'string');
    ylim2 = get(hs.Edit_Ylim2,'string');         
    ylim1 = str2double(ylim1);
	ylim2 = str2double(ylim2);
    
    % Si tienen sentido, los aplico
    if ylim2 > ylim1
        ylim([ylim1 ylim2]);
    end
    % si no tienen sentido queda el eje y como estaba.
    % Pero no aviso al usuario, porque esta función se llama todo el tiempo
    
end

end