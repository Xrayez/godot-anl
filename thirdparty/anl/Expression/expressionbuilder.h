#ifndef EXPRESSIONBUILDER_H
#define EXPRESSIONBUILDER_H

#include "parsing.h"
#include "../VM/kernel.h"
#include "../VM/random_gen.h"
#include <vector>
#include <string>
#include <map>

namespace anl
{
class CExpressionBuilder
{
public:
    CExpressionBuilder(CKernel &kernel);
    ~CExpressionBuilder();

    CInstructionIndex eval(const std::string &expr);
    CInstructionIndex evalAndStore(const std::string &expr);
    void store(CInstructionIndex i);
    std::vector<Token> getPostfix(const std::string &expr);
    void setRandomSeed(unsigned int seed);

    CInstructionIndex evalAndStoreVar(const std::string &varname, const std::string &expr);
    void storeVar(const std::string &varname, CInstructionIndex idx);
    CInstructionIndex retrieveVar(const std::string &varname);

private:
    CKernel &kernel_;
    std::vector<CInstructionIndex> index_;
    std::map<std::string, int> f_;  // Functions
    std::vector<std::string> vars_;
    std::map<std::string, CInstructionIndex> storedvars_;
    KISS prng_;

    void buildFunction(const std::string &token, std::stack<CInstructionIndex> &stk);
    void buildVar(const std::string &token, std::stack<CInstructionIndex> &stk);
};

#define DEFINE_TOKEN_NAME(m_function, m_name) \
	const std::string TokenNames::m_function = m_name;

#define DECLARE_TOKEN_NAME(m_function) \
	static const std::string m_function;

struct TokenNames
{
    DECLARE_TOKEN_NAME(valueBasis);
    DECLARE_TOKEN_NAME(gradientBasis);
    DECLARE_TOKEN_NAME(simplexBasis);
    DECLARE_TOKEN_NAME(cellularBasis);
    DECLARE_TOKEN_NAME(max);
    DECLARE_TOKEN_NAME(min);
    DECLARE_TOKEN_NAME(abs);
    DECLARE_TOKEN_NAME(bias);
    DECLARE_TOKEN_NAME(gain);
    DECLARE_TOKEN_NAME(scale);
    DECLARE_TOKEN_NAME(scaleX);
    DECLARE_TOKEN_NAME(scaleY);
    DECLARE_TOKEN_NAME(scaleZ);
    DECLARE_TOKEN_NAME(scaleW);
    DECLARE_TOKEN_NAME(scaleU);
    DECLARE_TOKEN_NAME(scaleV);
    DECLARE_TOKEN_NAME(translate);
    DECLARE_TOKEN_NAME(translateX);
    DECLARE_TOKEN_NAME(translateY);
    DECLARE_TOKEN_NAME(translateZ);
    DECLARE_TOKEN_NAME(translateW);
    DECLARE_TOKEN_NAME(translateU);
    DECLARE_TOKEN_NAME(translateV);
    DECLARE_TOKEN_NAME(rotateDomain);
    DECLARE_TOKEN_NAME(mix);
    DECLARE_TOKEN_NAME(select);
    DECLARE_TOKEN_NAME(clamp);
    DECLARE_TOKEN_NAME(cos);
    DECLARE_TOKEN_NAME(sin);
    DECLARE_TOKEN_NAME(tan);
    DECLARE_TOKEN_NAME(acos);
    DECLARE_TOKEN_NAME(asin);
    DECLARE_TOKEN_NAME(atan);
    DECLARE_TOKEN_NAME(tiers);
    DECLARE_TOKEN_NAME(smoothTiers);
    DECLARE_TOKEN_NAME(dx);
    DECLARE_TOKEN_NAME(dy);
    DECLARE_TOKEN_NAME(dz);
    DECLARE_TOKEN_NAME(dw);
    DECLARE_TOKEN_NAME(du);
    DECLARE_TOKEN_NAME(dv);
    DECLARE_TOKEN_NAME(sigmoid);
	DECLARE_TOKEN_NAME(randomize);
	DECLARE_TOKEN_NAME(fractal);
	DECLARE_TOKEN_NAME(step);
	DECLARE_TOKEN_NAME(linearStep);
	DECLARE_TOKEN_NAME(smoothStep);
	DECLARE_TOKEN_NAME(smootherStep);
	DECLARE_TOKEN_NAME(curveSection);
    DECLARE_TOKEN_NAME(index);
    DECLARE_TOKEN_NAME(rindex);

    DECLARE_TOKEN_NAME(color);

    // Vars
    DECLARE_TOKEN_NAME(rand);
    DECLARE_TOKEN_NAME(rand01);
    DECLARE_TOKEN_NAME(x);
    DECLARE_TOKEN_NAME(y);
    DECLARE_TOKEN_NAME(z);
    DECLARE_TOKEN_NAME(w);
    DECLARE_TOKEN_NAME(u);
    DECLARE_TOKEN_NAME(v);
    DECLARE_TOKEN_NAME(radial);

    // Arithmetic
    DECLARE_TOKEN_NAME(add);
    DECLARE_TOKEN_NAME(subtract);
    DECLARE_TOKEN_NAME(multiply);
    DECLARE_TOKEN_NAME(divide);
    DECLARE_TOKEN_NAME(pow);
};

}; // namespace anl

#endif
