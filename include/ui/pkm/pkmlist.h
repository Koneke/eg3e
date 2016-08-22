#undef MODULE_NAME
#define MODULE_NAME pkm_pkmlist

static void xlist_onSelection(GtkTreeSelection* selection, gpointer data);
static void xAddRow(int number, const char* name);
static GtkWidget* xcreateTreeView();
static GtkTreeModel* xcreateModel();

void THIS(setup);
