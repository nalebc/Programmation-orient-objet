/********************************************
* Titre: Travail pratique #6 - mainwindow.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ExceptionArgumentInvalide.h"


#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <algorithm>


Q_DECLARE_METATYPE(Membre*)
Q_DECLARE_METATYPE(Billet*)
Q_DECLARE_METATYPE(Coupon*)

using namespace std;

MainWindow::MainWindow(vector<Coupon*> coupons, vector<Membre*> membres, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), coupons_(coupons), membres_(membres)
{
    ui->setupUi(this);
    setup();

}


MainWindow::~MainWindow()
{
    for(auto membre : membres_)
        delete membre;

    for (auto coupon: coupons_)
         delete coupon;

    delete ui;
}

void MainWindow::setup(){
   setMenu();
   setUI();


   chargerCoupons();
   chargerBillets();
   chargerMembres();
   nettoyerVue();

}

void MainWindow::afficherMessage(QString msg) {
   QMessageBox::critical(this,"Erreur ", msg);
}

void MainWindow::setMenu() {
    QMenu* fichier = menuBar()->addMenu("Fichier");
    QAction* quitter = new QAction("Quitter");
    QAction* nettoyerVue = new QAction("Netoyer vue");
    connect(nettoyerVue,SIGNAL(triggered()), this, SLOT(nettoyerVue()));
    connect(quitter,SIGNAL(triggered() ), this, SLOT(close()));
    fichier->addAction(quitter);
    fichier->addAction(nettoyerVue);
    // TODO
}


void MainWindow::setUI(){

    //liste des billets
    QLabel* billetsLabel = new QLabel();
    billetsLabel->setText("Billets : ");
    listeBillets_ = new QListWidget(this);
    listeBillets_->setSortingEnabled(true);
   connect(listeBillets_,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectionnerBillet(QListWidgetItem*)));
// TODO

    // Boutons radios Type de billets
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier Solde", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass Solde", this));

    QHBoxLayout* boutonsRadioBilletsLayout = new QHBoxLayout();
    for(QRadioButton* bouton : boutonsRadioTypeBillets_)
        boutonsRadioBilletsLayout->addWidget(bouton);


    // Liste deroulante pour choisir le Membre
    choixMembreBillet_ = new QComboBox(this);
    choixMembreBillet_->addItem("Membres");
    ajouterMembresDansComboBox(choixMembreBillet_);

    //Champ pour le PNR
    editeurPNR_ = new QLineEdit();

    QHBoxLayout* pnrLayout = new QHBoxLayout();
    pnrLayout->addWidget(new QLabel("PNR : "));
    pnrLayout->addWidget(editeurPNR_);


    //Champ pour le prix
    editeurPrixBillet_ = new QLineEdit();
    editeurPrixBillet_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* prixBilletLayout = new QHBoxLayout();
    prixBilletLayout->addWidget(new QLabel("Prix : "));
    prixBilletLayout->addWidget(editeurPrixBillet_);


    //Champ pour l'Od
    editeurOD_ = new QLineEdit();

    QHBoxLayout* odBilletLayout = new QHBoxLayout();
    odBilletLayout->addWidget(new QLabel("Od : "));
    odBilletLayout->addWidget(editeurOD_);


    //Champ pour le Tarif du Billet
    choixTarifBillet_ = new QComboBox(this);
    choixTarifBillet_->addItem("Tarif Billet");
    choixTarifBillet_->addItem("Economie");
    choixTarifBillet_->addItem("Premium economie");
    choixTarifBillet_->addItem("Affaire");
    choixTarifBillet_->addItem("Premiere");

    //Champ pour la date de vol
    editeurDateVol_ = new QLineEdit();

    QHBoxLayout* dateVolLayout = new QHBoxLayout();
    dateVolLayout->addWidget(new QLabel("Date de Vol : "));
    dateVolLayout->addWidget(editeurDateVol_);


    //Champ pour le pourcentage solde du billet
    editeurPourcentageSoldeBillet_ = new QLineEdit();
    editeurPourcentageSoldeBillet_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* pourcentageSoldeBilletLayout = new QHBoxLayout();
    pourcentageSoldeBilletLayout->addWidget(new QLabel("Pourcentage Solde Billet : "));
    pourcentageSoldeBilletLayout->addWidget(editeurPourcentageSoldeBillet_);

    //Champ pour les jours restants
    editeurUtilisationsRestantesFlightPass_ = new QLineEdit();
    editeurUtilisationsRestantesFlightPass_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    editeurUtilisationsRestantesFlightPass_->setDisabled(true);

    QHBoxLayout* utilisationsRestantesLayout = new QHBoxLayout();
    utilisationsRestantesLayout->addWidget(new QLabel("Utilisations Restantes : "));
    utilisationsRestantesLayout->addWidget(editeurUtilisationsRestantesFlightPass_);
    QHBoxLayout* boutonBillet = new QHBoxLayout();
    boutonAjouterBillet =  new QPushButton("Ajouter Billet");
    boutonBillet->addWidget(boutonAjouterBillet);
    connect(boutonAjouterBillet,SIGNAL(clicked()), this, SLOT(ajouterBillet()));
    //Bouton ajouter billet
// TODO


    //ligne seprant les ajouts de billets
    //et les ajouts de coupons
    QFrame* horizontaleFrameLine = new QFrame();
    horizontaleFrameLine->setFrameShape(QFrame::HLine);

    //liste des coupons
    QLabel* couponsLabel = new QLabel();
    couponsLabel->setText("Coupons : ");
    listeCoupons_ = new QListWidget(this);
    listeCoupons_->setSortingEnabled(true);
    QObject::connect( listeCoupons_,SIGNAL(itemClicked(QListWidgetItem*)), this,SLOT(selectionnerCoupon(QListWidgetItem*)));



// TODO


    //Champ pour le code du coupon
    editeurCodeCoupon_ = new QLineEdit();

    QHBoxLayout* codeCouponLayout = new QHBoxLayout();
    codeCouponLayout->addWidget(new QLabel("Code : "));
    codeCouponLayout->addWidget(editeurCodeCoupon_);

    //Champ pour le rabais du coupon
    editeurRabaisCoupon_ = new QLineEdit();
    editeurRabaisCoupon_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* rabaisCouponLayout = new QHBoxLayout();
    rabaisCouponLayout->addWidget(new QLabel("Rabais : "));
    rabaisCouponLayout->addWidget(editeurRabaisCoupon_);

    //Champ pour le cout du coupon
    editeurCoutCoupon_ = new QLineEdit();
    editeurCoutCoupon_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* coutCouponLayout = new QHBoxLayout();
    coutCouponLayout->addWidget(new QLabel("Cout : "));
    coutCouponLayout->addWidget(editeurCoutCoupon_);

    QHBoxLayout* boutonCoupon = new QHBoxLayout();
    boutonAjouterCoupon =  new QPushButton("Ajouter Coupon");
    boutonCoupon->addWidget(boutonAjouterCoupon);
    connect(boutonAjouterCoupon,SIGNAL(clicked()), this, SLOT(ajouterCoupon()));


    //Bouton ajouter coupon
// TODO


    //ligne seprant les ajouts de coupons
    //et les informations des membres
    QFrame* horizontaleFrameLine2 = new QFrame();
    horizontaleFrameLine2->setFrameShape(QFrame::HLine);


    //selecteur pour les membres
    QComboBox* choixMembre = new QComboBox(this);
    choixMembre->addItem("Tout Afficher"); // Index 0
    choixMembre->addItem("Afficher Membres Reguliers"); // Index 1
    choixMembre->addItem("Afficher Membres Premium"); // Index 2
    connect(choixMembre,SIGNAL(currentIndexChanged(int)),this, SLOT(filtrerListe(int)));
// TODO

    //liste des membres
    QLabel* membresLabel = new QLabel();
    membresLabel->setText("Membres : ");
    listeMembres_ = new QListWidget(this);
    listeMembres_->setSortingEnabled(true);
    connect(listeMembres_,SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(selectionnerMembre(QListWidgetItem* )));


// TODO


    //Champ pour les points du Membres Regulier
    editeurPoints_ = new QLineEdit();
    editeurPoints_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    editeurPoints_->setDisabled(true);
    editeurPoints_->setText("N/a");

    QHBoxLayout* pointsMembreLayout = new QHBoxLayout();
    pointsMembreLayout->addWidget(new QLabel("Points : "));
    pointsMembreLayout->addWidget(editeurPoints_);



    //Champ pour les points cumules du Membres Regulier
    editeurPointsCumules_ = new QLineEdit();
    editeurPointsCumules_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* pointsCumMembreLayout = new QHBoxLayout();
    pointsCumMembreLayout->addWidget(new QLabel("Points Cumules : "));
    pointsCumMembreLayout->addWidget(editeurPointsCumules_);
    editeurPointsCumules_->setDisabled(true);
    editeurPointsCumules_->setText("N/a");

    //Champ pour les points cumules du Membres Regulier
    editeurJoursRestants_ = new QLineEdit();
    editeurJoursRestants_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* joursRestantsLayout = new QHBoxLayout();
    joursRestantsLayout->addWidget(new QLabel("Jours Restants : "));
    joursRestantsLayout->addWidget(editeurJoursRestants_);
    editeurJoursRestants_->setDisabled(true);
    editeurJoursRestants_->setText("N/a");




    //Layout de gauche
    QVBoxLayout* layoutHautGauche = new QVBoxLayout;

    layoutHautGauche->addWidget(billetsLabel);
    layoutHautGauche->addWidget(listeBillets_);

    layoutHautGauche->addWidget(couponsLabel);
    layoutHautGauche->addWidget(listeCoupons_);

    layoutHautGauche->addWidget(choixMembre);

    layoutHautGauche->addWidget(membresLabel);
    layoutHautGauche->addWidget(listeMembres_);

    //layout de droite
     QVBoxLayout* layoutHautDroite = new QVBoxLayout;
     layoutHautDroite->addWidget(choixMembreBillet_);
     layoutHautDroite->addLayout(boutonsRadioBilletsLayout);
     layoutHautDroite->addLayout(pnrLayout);
     layoutHautDroite->addLayout(prixBilletLayout);
     layoutHautDroite->addLayout(odBilletLayout);
     layoutHautDroite->addWidget(choixTarifBillet_);
     layoutHautDroite->addLayout(dateVolLayout);
     layoutHautDroite->addLayout(pourcentageSoldeBilletLayout);
     layoutHautDroite->addLayout(utilisationsRestantesLayout);
     layoutHautDroite->addLayout(boutonBillet);

//TODO


     layoutHautDroite->addWidget(horizontaleFrameLine);

     layoutHautDroite->addLayout(codeCouponLayout);
     layoutHautDroite->addLayout(rabaisCouponLayout);
     layoutHautDroite->addLayout(coutCouponLayout);
     layoutHautDroite->addLayout(boutonCoupon);
//TODO

     layoutHautDroite->addWidget(horizontaleFrameLine2);

     layoutHautDroite->addLayout(pointsMembreLayout);
     layoutHautDroite->addLayout(pointsCumMembreLayout);
     layoutHautDroite->addLayout(joursRestantsLayout);



    //ligne verticale
    QFrame* verticalFrameLine = new QFrame;
    verticalFrameLine->setFrameShape(QFrame::VLine);

    //Layout du haut
    QHBoxLayout* layoutHaut = new QHBoxLayout;
    layoutHaut->addLayout(layoutHautGauche);
    layoutHaut->addWidget(verticalFrameLine);
    layoutHaut->addLayout(layoutHautDroite);

    //Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutHaut);

    QWidget* widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);

    string title = "Bienvenue sur PolyAir !" ;
    setWindowTitle(title.c_str());



}


void MainWindow::chargerBillets(){
    listeBillets_->clear();

    for(Membre* membre: membres_){
        for(Billet* billet: membre->getBillets())
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(billet->getPnr()), listeBillets_);
            item->setData(Qt::UserRole, QVariant::fromValue<Billet*>(billet));
        }
    }

}

void MainWindow::chargerCoupons(){
    listeCoupons_->clear();
    for (auto coupon: coupons_){

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(coupon->getCode()), listeCoupons_);
        item->setData(Qt::UserRole, QVariant::fromValue<Coupon*>(coupon));
    }

}

void MainWindow::chargerMembres(){
    listeMembres_->clear();
    for (auto membre: membres_){

        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(membre->getNom()) , listeMembres_);
        item->setData(Qt::UserRole, QVariant::fromValue<Membre*>(membre));
    }
}

void MainWindow::ajouterMembresDansComboBox(QComboBox* list){
    for(Membre* membre : membres_){
        list->addItem(QString::fromStdString(membre->getNom()));
    }
}



void MainWindow::nettoyerVue() {

    nettoyerVueBillets();
    nettoyerVueCoupons();
    nettoyerVueMembres();

    // Listes
    listeBillets_->clearSelection();
    listeCoupons_->clearSelection();
    listeMembres_->clearSelection();
    chargerBillets();
    chargerCoupons();
    chargerMembres();
}

void MainWindow::nettoyerVueBillets(){
    editeurOD_->setDisabled(false);
    editeurOD_->clear();
    boutonAjouterBillet->setDisabled(false);

    editeurPNR_->setDisabled(false);
    editeurPNR_->clear();

    editeurPrixBillet_->setDisabled(false);
    editeurPrixBillet_->clear();

    choixTarifBillet_->setDisabled(false);
    choixTarifBillet_->setCurrentIndex(0);

    choixMembreBillet_->setDisabled(false);
    choixMembreBillet_->setCurrentIndex(0);
    editeurDateVol_->setDisabled(false);
    editeurDateVol_->clear();

    editeurPourcentageSoldeBillet_->setDisabled(false);
    editeurPourcentageSoldeBillet_->clear();

    editeurUtilisationsRestantesFlightPass_->setDisabled(true);
    editeurUtilisationsRestantesFlightPass_->clear();
    for_each(boutonsRadioTypeBillets_.begin(),boutonsRadioTypeBillets_.end(),[](QRadioButton* b) {b->setDisabled(false);  });

}

void MainWindow::nettoyerVueCoupons(){
    editeurCodeCoupon_->setDisabled(false);
    editeurCodeCoupon_->clear();

    editeurCoutCoupon_->setDisabled(false);
    editeurCoutCoupon_->clear();

    editeurRabaisCoupon_->setDisabled(false);
    editeurRabaisCoupon_->clear();

}

void MainWindow::nettoyerVueMembres(){
    editeurPoints_->setText("N/a");

    editeurPointsCumules_->setText("N/a");

    editeurJoursRestants_->setText("N/a");
    boutonAjouterCoupon->setDisabled(false);

}


void MainWindow::selectionnerBillet(QListWidgetItem* item){
    Billet* billet = item->data(Qt::UserRole).value<Billet*>();
    boutonAjouterBillet->setDisabled(true);
    editeurPNR_->setDisabled(true);
    editeurOD_->setDisabled(true);
    editeurPrixBillet_->setDisabled(true);
    editeurDateVol_->setDisabled(true);
    editeurPourcentageSoldeBillet_->setDisabled(true);
    choixTarifBillet_->setDisabled(true);
    choixMembreBillet_->setDisabled(true);

    int indexTarif = choixTarifBillet_->findText(QString::fromStdString(billet->formatTarif(billet->getTarif())));
    if (indexTarif != -1)
       choixTarifBillet_->setCurrentIndex(indexTarif);

    int indexMembre = choixMembreBillet_->findText(QString::fromStdString(billet->getNomPassager()));
    if(indexMembre != -1)
        choixMembreBillet_->setCurrentIndex(indexMembre);
    editeurPNR_->setText(QString::fromStdString( billet->getPnr()));
    editeurOD_->setText(QString::fromStdString(billet->getOd()));
    editeurPrixBillet_->setText(QString::number(billet->getPrix()));



    for(auto b : boutonsRadioTypeBillets_){
        b->setDisabled(true);
        if((typeid (*billet) == typeid (BilletRegulier) && b->text().endsWith("Regulier") )||
           (typeid (*billet) == typeid (BilletRegulierSolde)&&  b->text().endsWith("Regulier Solde")) ||
           (typeid (*billet) == typeid (FlightPass) &&  b->text().endsWith("FlightPass")) ||
           (typeid (*billet) == typeid (FlightPassSolde) && b->text().endsWith("FlightPass Solde") )){
            b->setChecked(true);
}

    }
    if(typeid(*billet) == typeid(BilletRegulier)){
        editeurDateVol_->setText( QString::fromStdString((dynamic_cast<BilletRegulier*>(billet)->getDateVol() )));
        editeurPourcentageSoldeBillet_->setText("N/a")  ;
        editeurUtilisationsRestantesFlightPass_->setText("N/a")  ;

    }
    else if (typeid (*billet) == typeid(BilletRegulierSolde)){
        editeurDateVol_->setText( QString::fromStdString((dynamic_cast<BilletRegulierSolde*>(billet)->getDateVol() )));
        editeurUtilisationsRestantesFlightPass_->setText("N/a")  ;
        editeurPourcentageSoldeBillet_->setText( QString("%1 %").arg(dynamic_cast<BilletRegulierSolde*>(billet)->getPourcentageSolde()));
        editeurPrixBillet_->setText(QString::number(dynamic_cast<BilletRegulierSolde*>(billet)->getPrixBase()));

       }
    else if (typeid(*billet) == typeid(FlightPassSolde) ){
        editeurUtilisationsRestantesFlightPass_->setText( QString("%1   ").arg((dynamic_cast<FlightPassSolde*>(billet)->getNbUtilisationsRestante())));
        editeurPourcentageSoldeBillet_->setText( QString("%1  %").arg((dynamic_cast<FlightPassSolde*>(billet)->getPourcentageSolde())));
        editeurDateVol_->setText("N/a")   ;
        editeurPrixBillet_->setText(QString::number(dynamic_cast<FlightPassSolde*>(billet)->getPrixBase()));

    }
    else if (typeid(*billet) == typeid(FlightPass) ){
        editeurDateVol_->setText("N/a")  ;
        editeurPourcentageSoldeBillet_->setText("N/a")  ;
        editeurUtilisationsRestantesFlightPass_->setText( QString("%1 ").arg((dynamic_cast<FlightPass*>(billet)->getNbUtilisationsRestante())));
}



    // TODO
}
void MainWindow::selectionnerCoupon(QListWidgetItem* item ){
    // TODO
    Coupon * c = item->data(Qt::UserRole).value<Coupon*>();
    editeurCodeCoupon_->setDisabled(true);
    editeurCoutCoupon_->setDisabled(true);
    editeurRabaisCoupon_->setDisabled(true);
    boutonAjouterCoupon->setDisabled(true);
    editeurCodeCoupon_->setText(QString::fromStdString(c->getCode()));
    editeurCoutCoupon_->setText(QString::number(c->getCout()));
    editeurRabaisCoupon_->setText(QString::number(c->getRabais()));






}
void MainWindow::selectionnerMembre(QListWidgetItem* item){
    // TODO
    Membre * m= item->data(Qt::UserRole).value<Membre*>();


    if(typeid(*m) == typeid(MembreRegulier)){
        editeurPoints_->setText((QString::number(  dynamic_cast<MembreRegulier*>(m)->getPoints())));
        editeurPointsCumules_->setText("N/a");
        editeurJoursRestants_->setText("N/a");
    }
    else if(typeid(*m) == typeid(MembrePremium)){
        editeurPoints_->setText(( QString::number( dynamic_cast<MembrePremium*>(m)->getPoints())));
        editeurPointsCumules_->setText((QString::number( dynamic_cast<MembrePremium*>(m)->getpointsCumulee())));
        editeurJoursRestants_->setText((QString::number( dynamic_cast<MembrePremium*>(m)->getJourRestants())));

    }
    else {
        editeurPointsCumules_->setText("N/a");
        editeurJoursRestants_->setText("N/a");
        editeurPoints_->setText("N/a");

    }



}
void MainWindow::ajouterBillet(){
    // TODO
    Billet* b;
   bool condition = true;
   for( QRadioButton* q : boutonsRadioTypeBillets_)
       if ( q->isChecked())
           condition = false;
    try{
        if(choixMembreBillet_->currentText() == "Membres" )
              throw ExceptionArgumentInvalide ( "Erreur: Le membre n'a pas été choisi");

        else if(editeurOD_->text().isEmpty())
            throw ExceptionArgumentInvalide ( "Erreur: Origine-Destination n'a pas été rempli");
        else if(editeurPNR_->text().isEmpty())
            throw ExceptionArgumentInvalide ( "Erreur: PNR n'a pas été rempli");
        else if(editeurPrixBillet_->text().isEmpty())
            throw ExceptionArgumentInvalide ( "Erreur: Le prix du billet n'a pas été rempli");


        else if(choixTarifBillet_->currentText() == "Tarif Billet")
              throw ExceptionArgumentInvalide ( "Erreur: Le tarif du billet n'a pas été choisi");
        else if(condition)
            throw ExceptionArgumentInvalide ( "Erreur: Le type du billet n'a pas été choisi");





    QRadioButton* selected;
    for_each(boutonsRadioTypeBillets_.begin(),boutonsRadioTypeBillets_.end(),[&selected](QRadioButton* q) {if(q->isChecked()) selected = q;});
    if(selected->text().endsWith("Regulier")){
        if (editeurDateVol_->text().isEmpty())
       throw ExceptionArgumentInvalide ( "Erreur: La date du billet n'a pas été rempli");
        b = new BilletRegulier(editeurPNR_->text().toStdString(),editeurPrixBillet_->text().toDouble(),editeurOD_->text().toStdString(),getTarifBillet(),
                               editeurDateVol_->text().toStdString());}
    else if(selected->text().endsWith("Regulier Solde")){
        if (editeurDateVol_->text().isEmpty())
       throw ExceptionArgumentInvalide ( "Erreur: La date du billet n'a pas été rempli");
        if(editeurPourcentageSoldeBillet_->text().isEmpty())
                    throw ExceptionArgumentInvalide ( "Erreur: Le pourcentage du billet n'a pas été rempli");
        b = new BilletRegulierSolde(editeurPNR_->text().toStdString(),editeurPrixBillet_->text().toDouble(),editeurOD_->text().toStdString(),getTarifBillet(),
                 editeurDateVol_->text().toStdString(),editeurPourcentageSoldeBillet_->text().toDouble());}

    else if(selected->text().endsWith("FlightPass")){
        b = new FlightPass(editeurPNR_->text().toStdString(),editeurPrixBillet_->text().toDouble(),editeurOD_->text().toStdString(),getTarifBillet());}


    else{

        if(editeurPourcentageSoldeBillet_->text().isEmpty())
                    throw ExceptionArgumentInvalide ( "Erreur: Le pourcentage du billet n'a pas été rempli");
        b = new FlightPassSolde(editeurPNR_->text().toStdString(),editeurPrixBillet_->text().toDouble(),editeurOD_->text().toStdString(),getTarifBillet(),
                                editeurPourcentageSoldeBillet_->text().toDouble());}

}
   catch(ExceptionArgumentInvalide& e){
       afficherMessage( e.what());
       return;

   }
    trouverMembreParNom( choixMembreBillet_->currentText().toStdString())->ajouterBillet(b);
    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b->getPnr()) , listeBillets_);
    item->setData(Qt::UserRole, QVariant::fromValue<Billet*>(b));
    item->setHidden(false);






}
void MainWindow::ajouterCoupon(){
        try { if(editeurCodeCoupon_->text().isEmpty() )
            throw ExceptionArgumentInvalide ( "Erreur: Le code n'a pas été rempli");
      else if (editeurCoutCoupon_->text().isEmpty())
          throw ExceptionArgumentInvalide ( "Erreur: Le cout n'a pas été rempli");
      else if(editeurRabaisCoupon_->text().isEmpty())
          throw ExceptionArgumentInvalide ( "Erreur: Le rabais n'a pas été rempli");
}
catch(ExceptionArgumentInvalide & e){
    afficherMessage(e.what());
    return;

    // TODO
}

    Coupon* coupon = new Coupon(editeurCodeCoupon_->text().toStdString(),editeurRabaisCoupon_->text().toDouble(),editeurCoutCoupon_->text().toInt());
    coupons_.push_back(coupon);
    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(  coupon->getCode() ) , listeCoupons_);
    item->setData(Qt::UserRole, QVariant::fromValue<Coupon*>(coupon));
    item->setHidden(false);


}


void MainWindow::filtrerListe(int index){
    for ( int i = 0 ; i < listeMembres_->count(); i++){
        QListWidgetItem * item = listeMembres_->item(i);
        Membre* membre = item->data(Qt::UserRole).value<Membre*>();
        item->setHidden(filtrerMasque(membre,index));

    }


}

bool MainWindow::filtrerMasque(Membre* membre, int index) {
    switch (index){
    case 0 : return (typeid (*membre) == typeid(Membre));
    case 1 : return (typeid (*membre) == typeid(MembrePremium));
    case 2 : return (typeid (*membre) == typeid(MembreRegulier));

    default: return false;
    }


}

TarifBillet MainWindow::getTarifBillet(){
//TODO
    if ( choixTarifBillet_->currentText() == "Premiere")
        return TarifBillet::Premiere;
    else if(choixTarifBillet_->currentText() == "Economie")
        return  TarifBillet::Economie;
    else if(choixTarifBillet_->currentText() == "Affaire")
        return  TarifBillet::Affaire;
    else
        return TarifBillet::PremiumEconomie;



    }




Membre* MainWindow::trouverMembreParNom(const string& nom){
   //TODO
   return *find_if(membres_.begin(),membres_.end(), [&nom](Membre* m){ return m->getNom() == nom;});
}
