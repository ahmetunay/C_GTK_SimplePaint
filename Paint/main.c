#include <gtk/gtk.h>
#include <strings.h>
#define MAX_POINT 4

int GRed = 0;
int GGreen = 0;
int GBlue = 0;
int Gwith=10;
int Gheight=10;
int change=1;
int GRound=60;
GdkGC *NewColor;
char newfilename[100]="C:\\Users\\Tunay\\Desktop\\new.jpg"; /// Yeni  fotoğraf oluşturmak için boş fotoğraf


GtkWidget *loadWindow;
GtkWidget *saveWindow;

GtkWidget *globalWindow;
GtkWidget *globalDrawingArea;
GtkWidget *globalDrawingArea2;
GtkWidget *globalVBox;
GtkWidget *globaLBox;
GtkWidget *globaLBox2;
GtkWidget *globalMenuBar;
GtkWidget *globalButton;
GtkWidget *globalLabel;

static GdkPixbuf *pixMap = NULL;
static GdkPixbuf *pix =NULL;
static GdkPoint *points;
int pointSelect=0;
gdouble selectedPointsX[MAX_POINT];
gdouble selectedPointsY[MAX_POINT];
int pointCounter=0;
int photoRead = 0;

static gint configure_event(GtkWidget *widget,GdkEventConfigure *event){
	if (pixMap)
		gdk_pixmap_unref(pixMap);
	pixMap = gdk_pixmap_new(widget->window,widget->allocation.width,widget->allocation.height,-1);
	gdk_draw_rectangle (pixMap,widget->style->white_gc,TRUE,0, 0,widget->allocation.width,widget->allocation.height);
	return TRUE;
}

static gint expose_event(GtkWidget *widget,GdkEventExpose *event){
	gdk_draw_pixmap(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE (widget)],pixMap,event->area.x, event->area.y,event->area.x, event->area.y,event->area.width, event->area.height);
    if(photoRead == 1){
        GdkPixbuf *pix;
        GError *err = NULL;
        pix = gdk_pixbuf_new_from_file(newfilename, &err);
        if(err)
        {
            printf("Error : %s\n", err->message);
            g_error_free(err);
            return FALSE;
        }
        GdkDrawable *draw = gtk_widget_get_window(widget);
        gdk_draw_pixbuf(draw, NULL, pix, 0, 0, 0, 0,-1,-1, GDK_RGB_DITHER_NONE, 0, 0);
        photoRead = 0;
    }
	return FALSE;
}

static void draw_brush(GtkWidget *widget,gdouble x,gdouble y){
	GdkRectangle update_rect;
	update_rect.x = x - Gwith/2;
	update_rect.y = y - Gheight/2;
	update_rect.width = Gwith;
	update_rect.height = Gheight;
	GdkColor *color;
	int width, height;

	GdkGC *NewColor; /// renk oluşumu
	NewColor = gdk_gc_new(widget->window);
	gdk_window_get_size(widget->window, &width, &height);

	color = (GdkColor *)malloc(sizeof(GdkColor));
	color->red = GRed * (0xFFFF/255);
	color->green = GGreen * (0xFFFF/255);
	color->blue = GBlue * (0xFFFF/255);
	color->pixel = (gulong)(GRed*256 + GGreen*256 + GBlue*256);
	gdk_color_alloc(gtk_widget_get_colormap(widget), color);
	gdk_gc_set_foreground(NewColor, color);
    if(pointSelect){
        selectedPointsX[pointCounter] = x;
        selectedPointsY[pointCounter] = y;
        pointCounter++;
        if(pointCounter >= MAX_POINT)
            pointCounter=0;
    }else{
        if(change==1){
            /// Main Draw Function
          gdk_draw_rectangle(pixMap,NewColor,TRUE,update_rect.x, update_rect.y,update_rect.width, update_rect.height);
        }
        else if(change==0){
        ///Round Draw Function
        gdk_draw_arc (pixMap,NewColor,TRUE,update_rect.x,update_rect.y, update_rect.width, update_rect.height,GRound, 100 * 360); //

        }

        gtk_widget_draw (widget, &update_rect);
    }
}

static gint button_press_event(GtkWidget *widget,GdkEventButton *event){
	if (event->button == 1 && pixMap != NULL)
    draw_brush (widget, event->x, event->y);
     if (event->type == GDK_BUTTON_PRESS  &&  event->button == 3){
        PointIntegrator(widget);
    }
	return TRUE;
}
static gint motion_notify_event(GtkWidget *widget,GdkEventMotion *event){
	int x, y;
	GdkModifierType state;
	if (event->is_hint)
		gdk_window_get_pointer (event->window, &x, &y, &state);
	else{
		x = event->x;
		y = event->y;
		state = event->state;
	}
	if (state & GDK_BUTTON1_MASK && pixMap != NULL)
		draw_brush (widget, x, y);
	return TRUE;
}

void quit (){
    /// Quit
	gtk_exit (0);
}

static void ChangeColor(GtkWidget *w,gpointer data){
  ///Change Color Function
    int *a = data;
    int r = 0;
    int g = 0;
    int b = 0;
    if(a == 1){
        ///White
        r = 255;
        g = 255;
        b = 255;
    }else if(a == 2){
      ///Black
        r = 0;
        g = 0;
        b = 0;
    }else if(a == 3){
       ///Red
        r = 255;
        g = 0;
        b = 0;
    }
    else if(a==4){
        ///Green
        r=0;
        g=255;
        b=0;
    }
    else if (a==5){
       ///Blue
        r=0;
        g=0;
        b=255;
    }
    else if(a==6){
       ///Yellow
        r=255;
        g=255;
        b=0;

    }
    else if(a==7){
       ///Purple
        r=255;
        g=0;
        b=255;
    }
    else if (a==8){
       ///Orange
        r=255;
        g=128;
        b=0;
    }
    GRed = r;
    GGreen = g;
    GBlue = b;
    change=1;
}

static void Pencil(GtkWidget *w){

pointSelect=0;
int height=10;
int with=10;
int r = 0;
int g = 0;
int b = 0;
Gwith=with;
Gheight=height;
GRed=r;
GBlue=b;
GGreen=g;
change=1;

}

static void Eraser(GtkWidget *w){

    pointSelect=0;
    int r = 255;
    int g = 255;
    int b = 255;
    int with=50;
    int heigh=50;
    Gwith=with;
    Gheight=heigh;
    GRed=r;
    GGreen=g;
    GBlue=b;
    change=1;
    }

void SavePhoto (GtkWidget *widget,gpointer data){

    GError * error = NULL;
    GdkPixbuf * pix2;
    pix2 = gdk_pixbuf_new(GDK_COLORSPACE_RGB,FALSE,8,800,800);
    gdk_pixbuf_get_from_drawable(pix2,globalDrawingArea->window,gdk_colormap_get_system(),0,0,0,0,800,800);

    error = NULL;
    gdk_pixbuf_save (pix2,newfilename, "jpeg", &error,"quality", "100"); ///The function of save changed pixbuff
    gtk_widget_hide(saveWindow);
}

void ReadPhoto (GtkWidget *widget,gpointer data){

    photoRead = 1;
    main2();
}

static void ReadPathPhotoText( GtkWidget *widget,GtkWidget *entry  ){

  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  strcpy(newfilename,entry_text);
}

void ReadPathPhoto( GtkWidget *widget, gpointer   data ){

    pointSelect=0;

    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;

    gint tmp_pos;
    gint tmp_pos2;

    /* create a new window */
    loadWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (loadWindow), 300, 300);
    gtk_window_set_title (GTK_WINDOW (loadWindow), "Aç-Yükle");
    g_signal_connect (loadWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect_swapped (loadWindow, "delete-event",G_CALLBACK (gtk_widget_destroy),loadWindow);

    vbox = gtk_vbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (loadWindow), vbox);
    gtk_widget_show (vbox);



    label = gtk_label_new ("Please write directory path then Click Enter\nYou must add .jpg or .png \nLast step Click Load Button");
    gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_widget_show (label);


    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 500);
    g_signal_connect (entry, "activate", G_CALLBACK (ReadPathPhotoText),entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "" );
    tmp_pos = GTK_ENTRY (entry)->text_length;

    gtk_editable_select_region (GTK_EDITABLE (entry),0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

 button = gtk_button_new_with_label("Read");
    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK (ReadPhoto) ,0);// gtk_signal_connect_full ((object), (name), (func), NULL, (func_data), NULL, 0, 0)
    gtk_widget_show(button);

hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_container_border_width (GTK_CONTAINER (hbox), 0);
    gtk_widget_show (hbox);

    gtk_widget_show (loadWindow);

    gtk_main();

}



static void SavePhotoPathText( GtkWidget *widget,GtkWidget *entry  ){

  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));

  strcpy(newfilename,entry_text);
}

void SavePhotoPath( GtkWidget *widget, gpointer   data ){
    pointSelect=0;

    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;

    gint tmp_pos;
    gint tmp_pos2;

    /* create a new window */
    saveWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (saveWindow), 300, 300);
    gtk_window_set_title (GTK_WINDOW (saveWindow), "Save");
    g_signal_connect (saveWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect_swapped (saveWindow, "delete-event",G_CALLBACK (gtk_widget_destroy),saveWindow);

    vbox = gtk_vbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (saveWindow), vbox);
    gtk_widget_show (vbox);


    label = gtk_label_new ("Please write directory path then Click Enter\nYou must add .jpg or .png \nLast step Click Load Button");
    gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_widget_show (label);


    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 500);
    g_signal_connect (entry, "activate", G_CALLBACK (SavePhotoPathText),entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "" );

    tmp_pos = GTK_ENTRY (entry)->text_length;

    gtk_editable_select_region (GTK_EDITABLE (entry),0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);


    button = gtk_button_new_with_label("Save");
    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK (SavePhoto) ,0);// gtk_signal_connect_full ((object), (name), (func), NULL, (func_data), NULL, 0, 0)
    gtk_widget_show(button);


    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_container_border_width (GTK_CONTAINER (hbox), 1);
    gtk_widget_show (hbox);


    gtk_widget_show (button);
    gtk_widget_show (saveWindow);

    gtk_main();

}

///ToolBar
static GtkItemFactoryEntry menu_items[] = {
	{ "/File/_New",     "<control>N", ReadPhoto,  0,  NULL },
	{ "/File/_Open-Load",    "<control>O", ReadPathPhoto,        0,  NULL }, // yükle
	{ "/File/_Save",    "<control>S", SavePhotoPath,        0,  NULL }, // kayit
	{ "/File/Quit",     "<control>Q", gtk_main_quit,0,  NULL },

};
void get_main_menu(GtkWidget  *window,GtkWidget **menubar){
	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;
	gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);
	accel_group = gtk_accel_group_new ();
	item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>",accel_group);
	gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);
	if (menubar)
	*menubar = gtk_item_factory_get_widget (item_factory, "<main>");
}

/// ////////////////////////////////////////////////////////
static void RecieveRectAngleText( GtkWidget *widget,GtkWidget *entry  ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  int num = atoi(entry_text);
  change=1;
  Gwith=num;

}
static void RecieveRectAngleText_2( GtkWidget *widget,GtkWidget *entry  ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  int num = atoi(entry_text);
  change=1;
  Gheight=num;

}
void RecieveRectAngle ( GtkWidget *widget, gpointer   data ){
    pointSelect=0;
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;

    gint tmp_pos;
    gint tmp_pos2;

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 300, 300);
    gtk_window_set_title (GTK_WINDOW (window), "RectAngle");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect_swapped (window, "delete-event",G_CALLBACK (gtk_widget_destroy),window);

    vbox = gtk_vbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Width");
    gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_widget_show (label);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (RecieveRectAngleText),entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "Width");
    tmp_pos = GTK_ENTRY (entry)->text_length;

    gtk_editable_select_region (GTK_EDITABLE (entry),0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

    button = gtk_button_new_with_label("Save");
    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK (RecieveRectAngleText) ,entry);// gtk_signal_connect_full ((object), (name), (func), NULL, (func_data), NULL, 0, 0)
    gtk_widget_show(button);


    label = gtk_label_new ("Height");
    gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_widget_show (label);


    entry2=gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry2),50);
    g_signal_connect (entry2, "activate", G_CALLBACK (RecieveRectAngleText_2),entry2);
    gtk_entry_set_text(GTK_ENTRY(entry2),"Height");
    tmp_pos2=GTK_ENTRY(entry2)->text_length;

    gtk_editable_select_region (GTK_EDITABLE (entry2),0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);

    button = gtk_button_new_with_label("Save");
    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK (RecieveRectAngleText_2) ,entry2);// gtk_signal_connect_full ((object), (name), (func), NULL, (func_data), NULL, 0, 0)
    gtk_widget_show(button);


    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_container_border_width (GTK_CONTAINER (hbox), 10);
    gtk_widget_show (hbox);


    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),window);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default (button, TRUE);
    gtk_widget_grab_default (button);


    gtk_widget_show (button);
    gtk_widget_show (window);
    gtk_main();

}
/// /////////////////////////////////////
/// /////////////////////////////////////
/// /////////////////////////////////////

void PointIntegrator(GtkWidget *widget){
	int i = 0;
    for(i = 0;i<pointCounter;i++){
        int Hedef = i+1;
        if(Hedef >= pointCounter)
            Hedef = 0;

        GdkColor *color;
        int width, height;

        NewColor = gdk_gc_new(widget->window);
        gdk_window_get_size(widget->window, &width, &height);

        color = (GdkColor *)malloc(sizeof(GdkColor));
        color->red = GRed * (0xFFFF/255);
        color->green = GGreen * (0xFFFF/255);
        color->blue = GBlue * (0xFFFF/255);
        color->pixel = (gulong)(GRed*256 + GGreen*256 + GBlue*256);
        gdk_color_alloc(gtk_widget_get_colormap(widget), color);
        gdk_gc_set_foreground(NewColor, color);


        gdk_draw_line(widget->window,NewColor,selectedPointsX[i],selectedPointsY[i],selectedPointsX[Hedef],selectedPointsY[Hedef]);

    }
    for(i=0;i<pointCounter;i++){
        selectedPointsX[i] = (gdouble)0;
        selectedPointsY[i] = (gdouble)0;
    }
    pointCounter=0;
}
void point ( GtkWidget *widget, gpointer   data ){
    pointSelect=1;
    int i = 0;
    for(i=0;i<pointCounter;i++){
        if (pointCounter<=2){
            selectedPointsX[i] = (gdouble)0;
            selectedPointsY[i] = (gdouble)0;
        }

    }
    pointCounter=0;
}
 /// ///////////////////////////////////////////////////////
 /// ///////////////////////////////////////////////////////
 /// ///////////////////////////////////////////////////////
static void RecieveSquareText( GtkWidget *widget,GtkWidget *entry  ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  int num = atoi(entry_text);
  change=1;
  Gwith=num;
  Gheight=num;

}
void RecieveSquare ( GtkWidget *widget, gpointer   data ){
    pointSelect=0;
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;

    gint tmp_pos;


    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 300, 300);
    gtk_window_set_title (GTK_WINDOW (window), "Square");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect_swapped (window, "delete-event",G_CALLBACK (gtk_widget_destroy),window);

    vbox = gtk_vbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Width with Height");
    gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_widget_show (label);


    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (RecieveSquareText),entry);

    tmp_pos = GTK_ENTRY (entry)->text_length;



    gtk_editable_select_region (GTK_EDITABLE (entry),0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

     button = gtk_button_new_with_label("Save");
    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK (RecieveSquareText) ,entry);// gtk_signal_connect_full ((object), (name), (func), NULL, (func_data), NULL, 0, 0)

    gtk_widget_show(button);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_container_border_width (GTK_CONTAINER (hbox), 10);
    gtk_widget_show (hbox);

    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),window);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default (button, TRUE);
    gtk_widget_grab_default (button);

    gtk_widget_show (button);
    gtk_widget_show (window);

    gtk_main();



}
/// ////////////////////////////////////////////////////////
static void RecieveRoundText( GtkWidget *widget,GtkWidget *entry  ){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  int num = atoi(entry_text);

    change=0;
    Gwith=num;
    Gheight=num;

}
void RecieveRound ( GtkWidget *widget, gpointer   data ){
    pointSelect=0;
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *label2;

    gint tmp_pos;

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 300, 300);
    gtk_window_set_title (GTK_WINDOW (window), "Round");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect_swapped (window, "delete-event",G_CALLBACK (gtk_widget_destroy),window);

    vbox = gtk_vbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Diameter");
    gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_widget_show (label);


    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (RecieveRoundText),entry);

    tmp_pos = GTK_ENTRY (entry)->text_length;

    gtk_editable_select_region (GTK_EDITABLE (entry),0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

     button = gtk_button_new_with_label("Save");
    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK (RecieveRoundText) ,entry);// gtk_signal_connect_full ((object), (name), (func), NULL, (func_data), NULL, 0, 0)

    gtk_widget_show(button);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_container_border_width (GTK_CONTAINER (hbox), 10);
    gtk_widget_show (hbox);

    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),window);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default (button, TRUE);
    gtk_widget_grab_default (button);

    gtk_widget_show (button);
    gtk_widget_show (window);

    gtk_main();


}
 /// ///////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////





/// //////////////////////////////////////////////////////////
static void entry_toggle_editable( GtkWidget *checkbutton,GtkWidget *entry ){
  gtk_editable_set_editable (GTK_EDITABLE (entry),GTK_TOGGLE_BUTTON (checkbutton)->active);
}
static void entry_toggle_visibility( GtkWidget *checkbutton,GtkWidget *entry ){
  gtk_entry_set_visibility (GTK_ENTRY (entry),
  GTK_TOGGLE_BUTTON (checkbutton)->active);
}


GtkWidget *make_box( gint homogeneous, gint spacing,gint expand,gint fill,gint padding ){


    GtkWidget *box;
    GtkWidget *button;
    char padstr[80];
    /* Create a new hbox with the appropriate homogeneous
     * and spacing settings */
    box = gtk_hbox_new (homogeneous, spacing);
    /* Create a series of buttons with the appropriate settings */

   button = gtk_button_new_with_label ("Red");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",ChangeColor ,3 );
    gtk_widget_show (button);

    button = gtk_button_new_with_label("Green");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",ChangeColor ,4);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Blue");
    gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",ChangeColor ,5);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Yellow");
    gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",ChangeColor ,6);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Purple");
    gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",ChangeColor ,7);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Orange");
    gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",ChangeColor ,8 );
    gtk_widget_show(button);
    return box;
}
GtkWidget *make_box2( gint homogeneous, gint spacing,gint expand,gint fill,gint padding ){

    GtkWidget *box;
    GtkWidget *button;
  char padstr[80];

    box = gtk_hbox_new (homogeneous, spacing);
    button = gtk_button_new_with_label ("Pencil");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",Pencil , 0);
	gtk_widget_show (button);

    button = gtk_button_new_with_label ("Eraser");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",Eraser ,0  );
    gtk_widget_show (button);


    button = gtk_button_new_with_label("Line");
    gtk_box_pack_start (GTK_BOX (box), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",point ,0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Round");
    gtk_box_pack_start (GTK_BOX (box), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",RecieveRound ,0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Square");
    gtk_box_pack_start (GTK_BOX (box), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",RecieveSquare ,0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("RectAngle");
    gtk_box_pack_start (GTK_BOX (box), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",RecieveRectAngle ,0);
    gtk_widget_show(button);


    button = gtk_button_new_with_label("Triangle");
    gtk_box_pack_start (GTK_BOX (box), button, 0, 0, 0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",point ,0);
    gtk_widget_show(button);




     return box;
    }


int main(int   argc,char *argv[]){
	gtk_init (&argc, &argv);

	globalWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(globalWindow), "Paint");

	globalVBox = gtk_vbox_new  (FALSE, 1); // Button boþluk ayarý ve  benzeri bir þey
	gtk_widget_show (globalVBox);


	gtk_signal_connect (GTK_OBJECT (globalWindow), "destroy",GTK_SIGNAL_FUNC (quit), NULL);
	gtk_container_border_width (GTK_CONTAINER (globalVBox), 10);
	gtk_container_add (GTK_CONTAINER (globalWindow), globalVBox);
    gtk_widget_show (globalVBox);

	get_main_menu (globalWindow, &globalMenuBar);
	gtk_box_pack_start (GTK_BOX (globalVBox), globalMenuBar, FALSE, TRUE, 0);
	gtk_widget_show (globalMenuBar);

    globalLabel = gtk_label_new ("Colors");
    gtk_misc_set_alignment (GTK_MISC (globalLabel), 0, 0);
    gtk_box_pack_start (GTK_BOX (globalVBox), globalLabel, FALSE, FALSE, 0);
    gtk_widget_show (globalLabel);

    globaLBox = make_box (FALSE, 0, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (globalVBox),globaLBox , FALSE, FALSE, 0);
    gtk_widget_show (globaLBox);

    globalLabel = gtk_label_new ("Tools");
    gtk_misc_set_alignment (GTK_MISC (globalLabel), 0, 0);
    gtk_box_pack_start (GTK_BOX (globalVBox), globalLabel, FALSE, FALSE, 0);
    gtk_widget_show (globalLabel);

    globaLBox2= make_box2(FALSE,0,FALSE,FALSE,0);
    gtk_box_pack_start (GTK_BOX (globalVBox),globaLBox2 , FALSE, FALSE, 0);
    gtk_widget_show (globaLBox2);



	/* cizim alani yaratma */

	globalDrawingArea = gtk_drawing_area_new ();
	gtk_drawing_area_size (GTK_DRAWING_AREA (globalDrawingArea), 800,800);
	gtk_box_pack_start (GTK_BOX (globalVBox), globalDrawingArea, 100, 0, 0);
	gtk_widget_show (globalDrawingArea);

	/* Signals used to handle backing pixMap */
	gtk_signal_connect (GTK_OBJECT (globalDrawingArea), "expose_event",(GtkSignalFunc) expose_event, NULL);
	gtk_signal_connect (GTK_OBJECT(globalDrawingArea),"configure_event",(GtkSignalFunc) configure_event, NULL);
	/* Event signals */
	gtk_signal_connect (GTK_OBJECT (globalDrawingArea), "motion_notify_event",(GtkSignalFunc) motion_notify_event, NULL); // kaydırma
	gtk_signal_connect (GTK_OBJECT (globalDrawingArea), "button_press_event",(GtkSignalFunc)button_press_event, NULL); // tıklama
	gtk_widget_set_events (globalDrawingArea, GDK_EXPOSURE_MASK| GDK_LEAVE_NOTIFY_MASK| GDK_BUTTON_PRESS_MASK| GDK_POINTER_MOTION_MASK| GDK_POINTER_MOTION_HINT_MASK);


	globalButton = gtk_button_new_with_label ("Quit");
	gtk_box_pack_start (GTK_BOX (globalVBox), globalButton, FALSE, FALSE, 0);
	gtk_signal_connect_object (GTK_OBJECT (globalButton), "clicked",GTK_SIGNAL_FUNC (gtk_widget_destroy),GTK_OBJECT (globalWindow));
	gtk_widget_show (globalButton);
	gtk_widget_show (globalWindow);

	gtk_main ();

	return 0;
}
void main2(){
    gtk_widget_hide(loadWindow);
    gtk_widget_hide(globalWindow);

    main(0,"");
}
