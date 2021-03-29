% show all 'Conexión' stuff, both platforms
function show_gui_Conexion(hObj)
    hs = guidata(hObj.Parent);
    
    % Platform selector
    set(hs.strPlatform,'visible','on');
    set(hs.ButGroup_Plataforma,'visible','on');
    set(hs.RadioBut_LPC1769,'visible','on');
    set(hs.RadioBut_Arduino,'visible','on');
    
    % Serial
    set(hs.strSerial,'visible','on');
    set(hs.Edit_Port,'visible','on');
    set(hs.Push_Open,'visible','on');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end