#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H

#include <vector>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"

class FuzzyModule
{
    private:

        std::map<std::string, FuzzyVariable*> varMap;;
        std::vector<FuzzyRule*> rules;

        //zeros the DOMs of the consequents of each rule. Used by Defuzzify()
        inline void SetConfidencesOfConsequentsToZero();

    public:
        FuzzyModule();
        virtual ~FuzzyModule();

        //creates a new "empty" fuzzy variable and returns a reference to it.
        FuzzyVariable& CreateFLV(const std::string& VarName);
        //adds a rule to the module
        void AddRule(FuzzySet& antecedent, FuzzySet& consequence);
        //this method calls the Fuzzify method of the named FLV
        inline void Fuzzify(const std::string& NameOfFLV, double val);
        //given a fuzzy variable and a defuzzification method this returns a
        //crisp value
        inline float DeFuzzify(const std::string& key);

};

#endif // FUZZYMODULE_H

/*
FuzzyModule fm;
FuzzyVariable& DistToTarget = fm.CreateFLV("DistToTarget");
FuzzyVariable& Desirability = fm.CreateFLV("Desirability");
FuzzyVariable& AmmoStatus   = fm.CreateFLV("AmmoStatus");
*/
/*
FuzzyModule fm;
FuzzyVariable& DistToTarget = fm.CreateFLV("DistToTarget");
FzSet Target_Close = DistToTarget.AddLeftShoulderSet("Target_Close",
                                                            0,
                                                            25,
                                                            150);
FzSet Target_Medium = DistToTarget.AddTriangularSet("Target_Medium",
                                                                25,
                                                                50,
                                                                300);
FzSet Target_Far = DistToTarget.AddRightShoulderSet("Target_Far",
                                                            150,
                                                            300,
                                                            500);
*/
/*
fm.AddRule(FzAND(Target_Far, Ammo_Low), Undesirable);

void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
    m_Rules.push_back(new FuzzyRule(antecedent, consequence)));
}

*/
/*
double CalculateDesirability(FuzzyModule& fm, double dist, double ammo)
{
    //fuzzify the inputs
    fm.Fuzzify("DistToTarget", dist);
    fm.Fuzzify("AmmoStatus", ammo);
    //this method automatically processes the rules and defuzzifies
    //the inferred conclusion
    return fm.DeFuzzify("Desirability", FuzzyModule::max_av);
}
*/
