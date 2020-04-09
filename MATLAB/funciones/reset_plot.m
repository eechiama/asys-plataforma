function plotHandle = reset_plot(hs)

axes(hs.Axis);
cla;
title('Muestras','fontsize',15);
xlabel('tiempo','fontsize',15);
set(hs.Axis, 'XLimMode', 'manual' );
set(hs.Axis, 'YLimMode', 'manual' );
% hace que al hacer plot() matlab no ponga los ejes que le parezca, deja
% los que están.


%% Chequeo ejes

% xlims
xlim1 = get(hs.Edit_Xlim1,'string');
xlim2 = get(hs.Edit_Xlim2,'string');

xlim1 = str2double(xlim1);
xlim2 = str2double(xlim2);

xlim([xlim1 xlim2]);

% ylims
ylim1 = get(hs.Edit_Ylim1,'string');
ylim2 = get(hs.Edit_Ylim2,'string');

ylim1 = str2double(ylim1);
ylim2 = str2double(ylim2);

ylim([ylim1 ylim2]);


%% Chequeo Grid

val = get(hs.Checkbox_Grid,'value');

if val == 0
    grid 'off';
end

if val == 1
    grid 'on';
end

end