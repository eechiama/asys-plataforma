function callback_TabSelect(hObj, event, pushedTabNumber)
% When a new TAB is selected:

% TAB changes:
%   All tab selection pushbuttons are greyed out
%   and panels are set to visible off
%   then the selected panel is made visible
%   and it's corresponding pushButton is highlighted.

% UI changes:
%   hide all GUI's
%   show GUI according to current TAB and platform

% Retrieve information from guiData and appData
hs = guidata(hObj.Parent);
uiInfo = getappdata(hs.Figure, 'uiInfo');


%% TABs changing
% For code legibility, assign these important values to variables
NumberOfTabs = uiInfo.NumberOfTabs;
TabHandles = hs.TabHandles;
TabLabels = uiInfo.TabLabels;
BGColor = uiInfo.BGColor;
White = uiInfo.White;

% Change selected tab to the corresponding pushed one.
uiInfo.SelectedTab = TabLabels{pushedTabNumber,1};
        
%   Turn all tabs off
for TabCount = 1:NumberOfTabs
    set(TabHandles{TabCount,1}, 'Visible', 'off');
    set(TabHandles{TabCount,2}, 'BackgroundColor', BGColor);
end

%   Enable the selected tab
set(TabHandles{pushedTabNumber,1}, 'Visible', 'on');        
set(TabHandles{pushedTabNumber,2}, 'BackgroundColor', White);

    
%% UI changing
% For code legibility, assign these important values to variables
platform = get(hs.ButGroup_Plataforma,'selectedobject');

% Hide all GUI's
hide_gui_adc(hObj);
hide_gui_buttonMode(hObj);
hide_gui_Conexion(hObj);
hide_gui_generator(hObj);
hide_gui_Plot(hObj);

% Case: Conexión
if( strcmp(uiInfo.SelectedTab, TabLabels{1,1}) )
    show_gui_Conexion(hObj);
end

% Case: ADC
if( strcmp(uiInfo.SelectedTab, TabLabels{2,1}) )
    show_gui_adc(hObj, platform);
end

% Case: PWM
if( strcmp(uiInfo.SelectedTab, TabLabels{3,1}) )
    show_gui_generator(hObj, platform);
end

% Case: PLOT
if( strcmp(uiInfo.SelectedTab, TabLabels{4,1}) )
    show_gui_plot(hObj, platform);
end

% Case: Conexión
% if( strcmp(uiInfo.SelectedTab, TabLabels{5,1}) )
%     show_gui_Conexion(hObj);
% end



end