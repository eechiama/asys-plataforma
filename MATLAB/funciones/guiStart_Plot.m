function hs = guiStart_Plot(hs)
% hs: the structure on which I keep all handles to objects.

%% Retrieve app data
uiInfo = getappdata(hs.Figure, 'uiInfo');
BGColor = uiInfo.BGColor;
White = uiInfo.White;

%% Guardar Muestras

% Check platform for establishing correct samples savepath.
if ispc
    uname = getenv('username');
    path = strcat('C:\',uname,'\muestras.txt');
elseif isunix
    path = '~/muestras.txt';
else
    path ='MAC idk';
end

% 'Guardar Muestras en' Text
hs.strSave = uicontrol(hs.Figure,'style','text');
set(hs.strSave,'BackgroundColor', BGColor);
set(hs.strSave,'units','normalized');
set(hs.strSave,'position',[0.64 0.77 0.25 0.05]);
set(hs.strSave,'string','Guardar muestras en:','fontsize',15);
set(hs.strSave,'visible','off');

% Filename
hs.Edit_File = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_File,'BackgroundColor', BGColor);
set(hs.Edit_File,'units','normalized');
set(hs.Edit_File,'position',[0.58 0.7 0.4 0.05]);
set(hs.Edit_File,'string', path,'fontsize',15);
set(hs.Edit_File,'visible','off');

%% PushButtons

% Guardar Muestras
hs.Push_Save = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Save,'BackgroundColor', BGColor);
set(hs.Push_Save,'units','normalized')
set(hs.Push_Save,'position',[0.6 0.5 0.18 0.1]);
set(hs.Push_Save,'string','Guardar Muestras','fontsize',15);
set(hs.Push_Save,'callback',@callback_guardar_muestras);
set(hs.Push_Save,'visible','off');

% ADC Start/Stop
hs.Toggle_StartStop = uicontrol(hs.Figure,'style','togglebutton');
set(hs.Toggle_StartStop,'BackgroundColor', BGColor);
set(hs.Toggle_StartStop,'units','normalized');
set(hs.Toggle_StartStop,'position', [0.8 0.5 0.18 0.1]);
set(hs.Toggle_StartStop,'string','Start ADC','fontsize',15);
set(hs.Toggle_StartStop,'callback',@callback_toggle_adc);
set(hs.Toggle_StartStop,'visible','off');

% PWM Start/Stop
hs.Toggle_pwm = uicontrol(hs.Figure,'style','togglebutton');
set(hs.Toggle_pwm,'BackgroundColor', BGColor);
set(hs.Toggle_pwm,'units','normalized');
set(hs.Toggle_pwm,'position', [0.6 0.35 0.18 0.1]);
set(hs.Toggle_pwm,'string','Start PWM','fontsize',15);
set(hs.Toggle_pwm,'callback',@callback_toggle_pwm);
set(hs.Toggle_pwm,'visible','off');




%% Plot section 'title' text

hs.strPlotConfig = uicontrol(hs.Figure,'style','text');
set(hs.strPlotConfig,'BackgroundColor', BGColor);
set(hs.strPlotConfig,'units','normalized');
set(hs.strPlotConfig,'position',[0.6 0.225 0.3 0.05]);
set(hs.strPlotConfig,'string','Configuración del Plot','fontsize',17);
set(hs.strPlotConfig,'visible','off');

%% Plot CONFIGS -- Xlim

% xlim Text
hs.strXlim = uicontrol(hs.Figure,'style','text');
set(hs.strXlim,'BackgroundColor', BGColor);
set(hs.strXlim,'units','normalized');
set(hs.strXlim,'position',[0.595 0.155 0.05 0.05]);
set(hs.strXlim,'string','xlim:','fontsize',15);
set(hs.strXlim,'visible','off');

% xlim1 Edit
hs.Edit_Xlim1 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Xlim1,'BackgroundColor', BGColor);
set(hs.Edit_Xlim1,'units','normalized');
set(hs.Edit_Xlim1,'position',[0.65 0.16 0.1 0.05]);
set(hs.Edit_Xlim1,'string','0','fontsize',15);
set(hs.Edit_Xlim1,'Enable','off');
set(hs.Edit_Xlim1,'visible','off');

% Guión xlim Text
hs.Text_Xlim_Guion = uicontrol(hs.Figure,'style','text');
set(hs.Text_Xlim_Guion,'BackgroundColor', BGColor);
set(hs.Text_Xlim_Guion,'units','normalized');
set(hs.Text_Xlim_Guion,'position',[0.75 0.16 0.03 0.05]);
set(hs.Text_Xlim_Guion,'string','-','fontsize',15);
set(hs.Text_Xlim_Guion,'visible','off');

% xlim2 Edit
hs.Edit_Xlim2 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Xlim2,'BackgroundColor', BGColor);
set(hs.Edit_Xlim2,'units','normalized');
set(hs.Edit_Xlim2,'position',[0.78 0.16 0.1 0.05]);
set(hs.Edit_Xlim2,'string','10','fontsize',15);
set(hs.Edit_Xlim2,'Enable','off');
set(hs.Edit_Xlim2,'visible','off');


%% Plot CONFIGS -- Ylim

% ylim Text
hs.strYlim = uicontrol(hs.Figure,'style','text');
set(hs.strYlim,'BackgroundColor', BGColor);
set(hs.strYlim,'units','normalized');
set(hs.strYlim,'position',[0.595 0.085 0.05 0.05]);
set(hs.strYlim,'string','ylim:','fontsize',15);
set(hs.strYlim,'visible','off');

% ylim1 Edit
hs.Edit_Ylim1 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Ylim1,'BackgroundColor', BGColor);
set(hs.Edit_Ylim1,'units','normalized');
set(hs.Edit_Ylim1,'position',[0.65 0.09 0.1 0.05]);
set(hs.Edit_Ylim1,'string','0','fontsize',15);
set(hs.Edit_Ylim1,'Enable','off');
set(hs.Edit_Ylim1,'visible','off');

% Guión ylim Text
hs.Text_Ylim_Guion = uicontrol(hs.Figure,'style','text');
set(hs.Text_Ylim_Guion,'BackgroundColor', BGColor);
set(hs.Text_Ylim_Guion,'units','normalized');
set(hs.Text_Ylim_Guion,'position',[0.75 0.09 0.03 0.05]);
set(hs.Text_Ylim_Guion,'string','-','fontsize',15);
set(hs.Text_Ylim_Guion,'visible','off');

% ylim2 Edit
hs.Edit_Ylim2 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Ylim2,'BackgroundColor', BGColor);
set(hs.Edit_Ylim2,'units','normalized');
set(hs.Edit_Ylim2,'position',[0.78 0.09 0.1 0.05]);
set(hs.Edit_Ylim2,'string','4096','fontsize',15);
set(hs.Edit_Ylim2,'Enable','off');
set(hs.Edit_Ylim2,'visible','off');

%% Plot CONFIGS -- CHECKBOXES

% Real-Time Checkbox
hs.Checkbox_RTP = uicontrol(hs.Figure,'style','checkbox');
set(hs.Checkbox_RTP,'BackgroundColor', BGColor);
set(hs.Checkbox_RTP,'units','normalized');
set(hs.Checkbox_RTP,'position',[0.57 0.02 0.17 0.05]);
set(hs.Checkbox_RTP,'string','  "Tiempo Real"','fontsize',14);
set(hs.Checkbox_RTP,'value',1);
set(hs.Checkbox_RTP,'callback',@callback_PlotOptionsCheck);
set(hs.Checkbox_RTP,'visible','off');

% Axis Tight Checkbox
hs.Checkbox_Tight = uicontrol(hs.Figure,'style','checkbox');
set(hs.Checkbox_Tight,'BackgroundColor', BGColor);
set(hs.Checkbox_Tight,'units','normalized');
set(hs.Checkbox_Tight,'position',[0.75 0.02 0.13 0.05]);
set(hs.Checkbox_Tight,'string','  Axis Tight','fontsize',14);
set(hs.Checkbox_Tight,'value',1);
set(hs.Checkbox_Tight,'callback',@callback_PlotOptionsCheck);
set(hs.Checkbox_Tight,'visible','off');

% Grid Checkbox
hs.Checkbox_Grid = uicontrol(hs.Figure,'style','checkbox');
set(hs.Checkbox_Grid,'BackgroundColor', BGColor);
set(hs.Checkbox_Grid,'units','normalized');
set(hs.Checkbox_Grid,'position',[0.89 0.02 0.1 0.05]);
set(hs.Checkbox_Grid,'string','  Grid','fontsize',14);
set(hs.Checkbox_Grid,'value',1);
set(hs.Checkbox_Grid,'visible','off');

%% PLOT Panel, Axes and Replot PushButton

% Panel
hs.plotPanel = uipanel(hs.Figure);
set(hs.plotPanel,'position', [0.01 0.01 0.55 0.82]);
set(hs.plotPanel,'visible','off');

% Axes
hs.Axis = axes(hs.plotPanel);
set(hs.Axis,'units','normalized');
%set(hs.Axis,'position', [0.1 0.1 0.3 0.3]);
set(hs.Axis,'box','on');
set(hs.Axis,'color',BGColor);
set(hs.Axis,'XColor','black');
set(hs.Axis,'YColor','black');
set(hs.Axis,'visible','on');
set(hs.Axis,'tag','a');
reset_plot(hs);

% Update Plot PushButton
hs.Push_UpdatePlot = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_UpdatePlot,'BackgroundColor', BGColor);
set(hs.Push_UpdatePlot,'units','normalized');
set(hs.Push_UpdatePlot,'position',[0.895 0.1 0.08 0.1]);
set(hs.Push_UpdatePlot,'string','RePlot','fontsize',15);
set(hs.Push_UpdatePlot,'callback',@callback_update_plot);
set(hs.Push_UpdatePlot,'Enable','off');
set(hs.Push_UpdatePlot,'visible','off');

end