% hide all 'Conexión' stuff, both platforms
function hide_gui_Conexion(hObj)
    hs = guidata(hObj.Parent);
    
    % Platform selector
    set(hs.strPlatform,'visible','off');
    set(hs.ButGroup_Plataforma,'visible','off');
    set(hs.RadioBut_LPC1769,'visible','off');
    set(hs.RadioBut_Arduino,'visible','off');
    
    % Serial
    set(hs.strSerial,'visible','off');
    set(hs.Edit_Port,'visible','off');
    set(hs.Push_Open,'visible','off');
    
    % Save changed handles to handles structure on guiData
    guidata(hObj.Parent,hs);
end