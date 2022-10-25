#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WDoubleValidator.h>
#include <Wt/WTextArea.h>
#include "../includes/numcpp.hpp"



class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);

private:
    std::vector<double> xi;
    std::vector<double> yi;
    std::vector<double> xMissing;
    std::vector<double> yMissing;
    int counter;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Data Interpolation");

    Wt::WText *InitialExplanation = root()->addWidget(std::make_unique<Wt::WText>());

    InitialExplanation->setText("<h1>Welcome!</h1> <p>This is a page that will allow you to interpolate the value at a point in the domain of your dataset, using other points in your dataset.</p><p> I used Lagrange Interpolation for this calculation.</p><p> Created By Vashist Hegde.</p><p>INSTRUCTION: enter value in the text boxes before clicking the add buttons.</p>");

    root()->addWidget(std::make_unique<Wt::WBreak>());


    //NOTE: using vectors was giving me segmentation fault because push_back invalidates
    //all references to elements in that vector.
    //https://stackoverflow.com/questions/34708189/c-vector-of-pointer-loses-the-reference-after-push-back

    

    int index=0;

    Wt::WText *directions = root()->addWidget(std::make_unique<Wt::WText>("Enter the list of points available to you from your data set:"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
    

    Wt::WText *xTextTemp = root()->addWidget(std::make_unique<Wt::WText>("X: "));
    Wt::WLineEdit *lineEdit1 = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WText *yTextTemp = root()->addWidget(std::make_unique<Wt::WText>("Y: "));
    Wt::WLineEdit *lineEdit2 = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    root()->addWidget(std::make_unique<Wt::WBreak>());
    Wt::WPushButton *button1 = root()->addWidget(std::make_unique<Wt::WPushButton>("Add Data Points"));

    //store the input xi and yi points
    auto addDataPoint = [this,lineEdit1,lineEdit2] () mutable{

        xi.push_back(std::stod(lineEdit1->text()));
        yi.push_back(std::stod(lineEdit2->text()));

        
        lineEdit1->setText("");
        lineEdit2->setText("");
        

    };

    button1->clicked().connect(addDataPoint);

    root()->addWidget(std::make_unique<Wt::WBreak>());

    Wt::WText *options = root()->addWidget(std::make_unique<Wt::WText>("Enter the domain point(s) for which you would like to interpolate values:"));

    root()->addWidget(std::make_unique<Wt::WBreak>());

    Wt::WText *xMissingText = root()->addWidget(std::make_unique<Wt::WText>("X_missing: "));
    

    Wt::WLineEdit *lineEdit3 = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    root()->addWidget(std::make_unique<Wt::WBreak>());
    Wt::WPushButton *button2 = root()->addWidget(std::make_unique<Wt::WPushButton>("Add point"));

    auto storeXMissing = [this,lineEdit3](){
        xMissing.push_back(std::stod(lineEdit3->text()));
        lineEdit3->setText("");
    };

    button2->clicked().connect(storeXMissing);

    root()->addWidget(std::make_unique<Wt::WBreak>());

    Wt::WPushButton *button3 = root()->addWidget(std::make_unique<Wt::WPushButton>("COMPUTE"));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    // auto container = std::make_unique<Wt::WContainerWidget>();
    // Wt::WText *out = container->addNew<Wt::WText>("<p></p>");
    // out->addStyleClass("help-block");

    auto compute = [this](){
        LagrangeInterp interpolator;
        counter++;
        
        if(xMissing.size()==1){
            std::cout<<xMissing[0]<<"\n";
            auto temp = interpolator.interpolate(xi,yi,xMissing[0]);
            yMissing.push_back(temp);
        }
        else{
            
            yMissing = interpolator.interpolate(xi,yi,xMissing);
            
        }
        Wt::WText *separator1 = root()->addWidget(std::make_unique<Wt::WText>("<p>Attempt "+std::to_string(counter)+"----------------------------------------------</p>"));
        for(int i=0;i<yMissing.size();i++){
            root()->addWidget(std::make_unique<Wt::WBreak>());
            Wt::WText *XText = root()->addWidget(std::make_unique<Wt::WText>("X: "));
            Wt::WText *XValue = root()->addWidget(std::make_unique<Wt::WText>());
            XValue->setText(std::to_string(xMissing[i]));
            Wt::WText *YText = root()->addWidget(std::make_unique<Wt::WText>("Y: "));
            Wt::WText *YValue = root()->addWidget(std::make_unique<Wt::WText>());
            YValue->setText(std::to_string(yMissing[i]));
        }
        Wt::WText *separator2 = root()->addWidget(std::make_unique<Wt::WText>("<p>----------------------------------------------</p>"));


    };
    button3->clicked().connect(compute);

    root()->addWidget(std::make_unique<Wt::WBreak>());

    Wt::WPushButton *button4 = root()->addWidget(std::make_unique<Wt::WPushButton>("Reset (click here to try again)"));

    auto reset = [this](){
        xi.clear();
        yi.clear();
        xMissing.clear();
        yMissing.clear();

    };
    button4->clicked().connect(reset);


}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<HelloApplication>(env);
    });
}