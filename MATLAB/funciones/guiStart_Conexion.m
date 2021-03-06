function hs = guiStart_Conexion(hs)
% hs: the structure on which I keep all handles to objects.

%% Retrieve app data
uiInfo = getappdata(hs.Figure, 'uiInfo');
BGColor = uiInfo.BGColor;
White = uiInfo.White;

%% Selector de Plataforma

% Plataforma Text
hs.strPlatform = uicontrol(hs.Figure,'style','text');
set(hs.strPlatform,'BackgroundColor', BGColor);
set(hs.strPlatform,'units','normalized');
set(hs.strPlatform,'position',[0.07 0.7 0.3 0.05]);
set(hs.strPlatform,'string','Plataforma de adquisición:','fontsize',15);
set(hs.strPlatform,'visible','on');

% Plataforma ButtonGroup 
hs.ButGroup_Plataforma = uibuttongroup('Visible','on');
set(hs.ButGroup_Plataforma,'units', 'normalized');
set(hs.ButGroup_Plataforma,'position', [0.4 0.695 0.5 0.06]);
set(hs.ButGroup_Plataforma,'SelectionChangedFcn',@callback_radiobutt_Plataforma);
set(hs.ButGroup_Plataforma,'visible','on');

% Plataforma RadioButton Infotronic v1
hs.RadioBut_LPC1769 = uicontrol(hs.ButGroup_Plataforma,'Style', 'radiobutton');
set(hs.RadioBut_LPC1769,'units','normalized');
set(hs.RadioBut_LPC1769,'position',[0.05 0.25 0.4 0.5]);
set(hs.RadioBut_LPC1769,'String','Infotronic v1 (LPC1769)');
set(hs.RadioBut_LPC1769,'HandleVisibility','off');
set(hs.RadioBut_LPC1769,'visible','on');

% Plataforma RadioButton Arduino
hs.RadioBut_Arduino = uicontrol(hs.ButGroup_Plataforma,'Style', 'radiobutton');
set(hs.RadioBut_Arduino,'units','normalized');
set(hs.RadioBut_Arduino,'position',[0.5 0.25 0.25 0.5]);
set(hs.RadioBut_Arduino,'String','Arduino');
set(hs.RadioBut_Arduino,'HandleVisibility','off');
set(hs.RadioBut_Arduino,'visible','on');

% Plataforma RadioButton LPC845
hs.RadioBut_LPC845 = uicontrol(hs.ButGroup_Plataforma,'Style', 'radiobutton');
set(hs.RadioBut_LPC845,'units','normalized');
set(hs.RadioBut_LPC845,'position',[0.8 0.25 0.2 0.5]);
set(hs.RadioBut_LPC845,'String','LPC845');
set(hs.RadioBut_LPC845,'HandleVisibility','off');
set(hs.RadioBut_LPC845,'visible','on');

set(hs.ButGroup_Plataforma,'selectedobject',hs.RadioBut_LPC1769);


%% Puerto Serie

% SerialPort Text
hs.strSerial = uicontrol(hs.Figure,'style','text');
set(hs.strSerial,'BackgroundColor',BGColor);
set(hs.strSerial,'units','normalized');
set(hs.strSerial,'position',[0.07 0.6 0.15 0.05]);
set(hs.strSerial,'string','Serial Port:','fontsize',15);
set(hs.strSerial,'visible','on');

% PortName Edit
hs.Edit_Port = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Port,'BackgroundColor',White);
set(hs.Edit_Port,'units','normalized');
set(hs.Edit_Port,'position',[0.4 0.6 0.25 0.05]);
set(hs.Edit_Port,'string','/dev/ttyUSB0','fontsize',15);
set(hs.Edit_Port,'visible','on');

% Open Serial
hs.Push_Open = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Open,'BackgroundColor',BGColor);
set(hs.Push_Open,'units','normalized');
set(hs.Push_Open,'position',[0.4 0.525 0.15 0.05]);
set(hs.Push_Open,'string','Open Serial','fontsize',15);
set(hs.Push_Open,'callback',@callback_Serial_Open);
set(hs.Push_Open,'visible','on');
end