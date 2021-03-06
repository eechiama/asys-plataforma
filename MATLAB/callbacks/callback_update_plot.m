function callback_update_plot(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
muestras = getappdata(hs.Figure,'muestras');

ll=length(muestras);
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

%% Chequeo ejes

val = get(hs.Checkbox_Tight,'value');

if val == 1
    axis('tight');
end

if val == 0
    
    % xlims
    xlim1 = get(hs.Edit_Xlim1,'string');
    xlim2 = get(hs.Edit_Xlim2,'string');
    
    xlim1 = str2double(xlim1);
    xlim2 = str2double(xlim2);
    
    % Si tienen sentido, los aplico
    if xlim2 > xlim1
        xlim([xlim1 xlim2]);
    end
    % si no tienen sentido queda el eje x como estaba, pero aviso al user
    if xlim2 <= xlim1
        errordlg('Los valores para xlim no tienen mucho sentido.');
    end
    
    
    
    % ylims
    ylim1 = get(hs.Edit_Ylim1,'string');
    ylim2 = get(hs.Edit_Ylim2,'string');
    
    ylim1 = str2double(ylim1);
    ylim2 = str2double(ylim2);
    
    % Si tienen sentido, los aplico
    if ylim2 > ylim1
        ylim([ylim1 ylim2]);
    end
    % si no tienen sentido queda el eje y como estaba, pero aviso al user
    if ylim2 <= ylim1
        errordlg('Los valores para ylim no tienen mucho sentido.');
    end
    
end
    
end
