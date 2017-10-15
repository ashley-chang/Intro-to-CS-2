void listAll(const MenuItem* m, string path) // two-parameter overload
{
    string newPath = path;
    //If the path is empty
    if (path.empty())
    {
        newPath = m->name();
    }
    else
    {
        newPath = path + "/" + m->name();
    }
    if (!newPath.empty())
        cout << newPath << endl;
    
    if (m->menuItems() == nullptr)
        return;
    for (int i = 0 ; i < m->menuItems()->size(); i++)
    {
        listAll(m->menuItems()->at(i), newPath);
    }
}
