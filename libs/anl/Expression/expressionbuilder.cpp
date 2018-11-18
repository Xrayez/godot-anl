#include "expressionbuilder.h"

#include <iostream>

template<class Container, class V>
std::pair<typename Container::iterator, bool> insert_or_assign(Container & c, typename Container::key_type const & k, V && v)
{
    auto itor = c.find(k);
    if(itor == c.end())
    {
        return c.emplace(k, std::forward<V>(v));
    }
    else
    {
        itor->second = std::forward<V>(v);
        return std::make_pair(itor, false);
    }
}

template<class C, class V>
std::pair<typename C::iterator, bool> insert_or_assign(C & c, typename C::key_type && k, V && v)
{
    auto itor = c.find(k);
    if(itor == c.end())
    {
        return c.emplace(std::move(k), std::forward<V>(v));
    }
    else
    {
        itor->second = std::forward<V>(v);
        return std::make_pair(itor, false);
    }
}

namespace anl
{

DEFINE_TOKEN_NAME(max, "max");
DEFINE_TOKEN_NAME(min, "min");
DEFINE_TOKEN_NAME(abs, "abs");
DEFINE_TOKEN_NAME(bias, "bias");
DEFINE_TOKEN_NAME(gain, "gain");
DEFINE_TOKEN_NAME(scale, "scale");
DEFINE_TOKEN_NAME(translate, "translate");
DEFINE_TOKEN_NAME(mix, "mix");
DEFINE_TOKEN_NAME(select, "select");
DEFINE_TOKEN_NAME(clamp, "clamp");
DEFINE_TOKEN_NAME(cos, "cos");
DEFINE_TOKEN_NAME(sin, "sin");
DEFINE_TOKEN_NAME(tan, "tan");
DEFINE_TOKEN_NAME(acos, "acos");
DEFINE_TOKEN_NAME(asin, "asin");
DEFINE_TOKEN_NAME(atan, "atan");
DEFINE_TOKEN_NAME(tiers, "tiers");
DEFINE_TOKEN_NAME(dx, "dx");
DEFINE_TOKEN_NAME(dy, "dy");
DEFINE_TOKEN_NAME(dz, "dz");
DEFINE_TOKEN_NAME(dw, "dw");
DEFINE_TOKEN_NAME(du, "du");
DEFINE_TOKEN_NAME(dv, "dv");
DEFINE_TOKEN_NAME(sigmoid, "sigmoid");
DEFINE_TOKEN_NAME(randomize, "randomize");
DEFINE_TOKEN_NAME(fractal, "fractal");
DEFINE_TOKEN_NAME(step, "step");
DEFINE_TOKEN_NAME(index, "index");
DEFINE_TOKEN_NAME(rindex, "rindex");

DEFINE_TOKEN_NAME(color, "color");

// Vars
DEFINE_TOKEN_NAME(rand," rand");
DEFINE_TOKEN_NAME(rand01," rand01");
DEFINE_TOKEN_NAME(x, "x");
DEFINE_TOKEN_NAME(y, "y");
DEFINE_TOKEN_NAME(z, "z");
DEFINE_TOKEN_NAME(w, "w");
DEFINE_TOKEN_NAME(u, "u");
DEFINE_TOKEN_NAME(v, "v");
DEFINE_TOKEN_NAME(radial, "radial");

// Arithmetic
DEFINE_TOKEN_NAME(add, "+");
DEFINE_TOKEN_NAME(subtract, "-");
DEFINE_TOKEN_NAME(multiply, "*");
DEFINE_TOKEN_NAME(divide, "/");
DEFINE_TOKEN_NAME(pow, "^");

#ifdef ANL_EXPRESSION_BUILDER_CAMELCASE
    DEFINE_TOKEN_NAME(valueBasis, "valueBasis");
    DEFINE_TOKEN_NAME(gradientBasis, "gradientBasis");
    DEFINE_TOKEN_NAME(simplexBasis, "simplexBasis");
    DEFINE_TOKEN_NAME(cellularBasis, "cellularBasis");
    DEFINE_TOKEN_NAME(scaleX, "scaleX");
    DEFINE_TOKEN_NAME(scaleY, "scaleY");
    DEFINE_TOKEN_NAME(scaleZ, "scaleZ");
    DEFINE_TOKEN_NAME(scaleW, "scaleW");
    DEFINE_TOKEN_NAME(scaleU, "scaleU");
    DEFINE_TOKEN_NAME(scaleV, "scaleV");
    DEFINE_TOKEN_NAME(translateX, "translateX");
    DEFINE_TOKEN_NAME(translateY, "translateY");
    DEFINE_TOKEN_NAME(translateZ, "translateZ");
    DEFINE_TOKEN_NAME(translateW, "translateW");
    DEFINE_TOKEN_NAME(translateU, "translateU");
    DEFINE_TOKEN_NAME(translateV, "translateV");
    DEFINE_TOKEN_NAME(rotateDomain, "rotateDomain");
    DEFINE_TOKEN_NAME(smoothTiers, "smoothTiers");
    DEFINE_TOKEN_NAME(linearStep, "linearStep");
    DEFINE_TOKEN_NAME(smoothStep, "smoothStep");
    DEFINE_TOKEN_NAME(smootherStep, "smootherStep");
    DEFINE_TOKEN_NAME(curveSection, "curveSection");
#else
    DEFINE_TOKEN_NAME(valueBasis, "value_basis");
    DEFINE_TOKEN_NAME(gradientBasis, "gradient_basis");
    DEFINE_TOKEN_NAME(simplexBasis, "simplex_basis");
    DEFINE_TOKEN_NAME(cellularBasis, "cellular_basis");
    DEFINE_TOKEN_NAME(scaleX, "scale_x");
    DEFINE_TOKEN_NAME(scaleY, "scale_y");
    DEFINE_TOKEN_NAME(scaleZ, "scale_z");
    DEFINE_TOKEN_NAME(scaleW, "scale_w");
    DEFINE_TOKEN_NAME(scaleU, "scale_u");
    DEFINE_TOKEN_NAME(scaleV, "scale_v");
    DEFINE_TOKEN_NAME(translateX, "translate_x");
    DEFINE_TOKEN_NAME(translateY, "translate_y");
    DEFINE_TOKEN_NAME(translateZ, "translate_z");
    DEFINE_TOKEN_NAME(translateW, "translate_w");
    DEFINE_TOKEN_NAME(translateU, "translate_u");
    DEFINE_TOKEN_NAME(translateV, "translate_v");
    DEFINE_TOKEN_NAME(rotateDomain, "rotate");
    DEFINE_TOKEN_NAME(smoothTiers, "smooth_tiers");
    DEFINE_TOKEN_NAME(linearStep, "linear_step");
    DEFINE_TOKEN_NAME(smoothStep, "smooth_step");
    DEFINE_TOKEN_NAME(smootherStep, "smoother_step");
    DEFINE_TOKEN_NAME(curveSection, "curve_section");
#endif

CExpressionBuilder::CExpressionBuilder(CKernel &kernel) : kernel_(kernel)
{
    f_[TokenNames::valueBasis]=2;
    f_[TokenNames::gradientBasis]=2;
    f_[TokenNames::simplexBasis]=1;
    f_[TokenNames::cellularBasis]=10;
    f_[TokenNames::max]=2;
    f_[TokenNames::min]=2;
    f_[TokenNames::abs]=1;
    f_[TokenNames::bias]=2;
    f_[TokenNames::gain]=2;
    f_[TokenNames::scale]=2;
    f_[TokenNames::scaleX]=2;
    f_[TokenNames::scaleY]=2;
    f_[TokenNames::scaleZ]=2;
    f_[TokenNames::scaleW]=2;
    f_[TokenNames::scaleU]=2;
    f_[TokenNames::scaleV]=2;
    f_[TokenNames::translate]=2;
    f_[TokenNames::translateX]=2;
    f_[TokenNames::translateY]=2;
    f_[TokenNames::translateZ]=2;
    f_[TokenNames::translateW]=2;
    f_[TokenNames::translateU]=2;
    f_[TokenNames::translateV]=2;
    f_[TokenNames::rotateDomain]=5;
    f_[TokenNames::mix]=3;
    f_[TokenNames::select]=5;
    f_[TokenNames::clamp]=3;
    f_[TokenNames::cos]=1;
    f_[TokenNames::sin]=1;
    f_[TokenNames::tan]=1;
    f_[TokenNames::acos]=1;
    f_[TokenNames::asin]=1;
    f_[TokenNames::atan]=1;
    f_[TokenNames::tiers]=2;
    f_[TokenNames::smoothTiers]=2;
    f_[TokenNames::dx]=1;
    f_[TokenNames::dy]=1;
    f_[TokenNames::dz]=1;
    f_[TokenNames::dw]=1;
    f_[TokenNames::du]=1;
    f_[TokenNames::dv]=1;
    f_[TokenNames::sigmoid]=3;
	f_[TokenNames::randomize]=3;
	f_[TokenNames::fractal]=6;
	f_[TokenNames::step]=2;
	f_[TokenNames::linearStep]=3;
	f_[TokenNames::smoothStep]=3;
	f_[TokenNames::smootherStep]=3;
	f_[TokenNames::curveSection]=5;
    f_[TokenNames::index]=1;
    f_[TokenNames::rindex]=1;

    f_[TokenNames::color]=4;

    // Build vars
    vars_.push_back(TokenNames::rand);
    vars_.push_back(TokenNames::rand01);
    vars_.push_back(TokenNames::x);
    vars_.push_back(TokenNames::y);
    vars_.push_back(TokenNames::z);
    vars_.push_back(TokenNames::w);
    vars_.push_back(TokenNames::u);
    vars_.push_back(TokenNames::v);
    vars_.push_back(TokenNames::radial);

}
CExpressionBuilder::~CExpressionBuilder() {}

void CExpressionBuilder::setRandomSeed(unsigned int seed)
{
    prng_.setSeed(seed);
}

std::vector<Token> CExpressionBuilder::getPostfix(const std::string &expr)
{
    ExpressionToPostfix e(expr, f_, vars_);
    return e.ToPostfix();
}

CInstructionIndex CExpressionBuilder::eval(const std::string &expr)
{
    ExpressionToPostfix e(expr, f_, vars_);

    auto p=e.ToPostfix();
    std::stack<CInstructionIndex> stk;

    for(auto i : p)
    {
        if(i.GetType()==Token::NUMBER)
        {
            stk.push(kernel_.constant(std::stod(i.GetToken())));
        }
        else if(i.GetType()==Token::OPERATOR)
        {
            CInstructionIndex right=stk.top();
            stk.pop();
            CInstructionIndex left=stk.top();
            stk.pop();
            if(i.GetToken()==TokenNames::add) stk.push(kernel_.add(left,right));
            else if(i.GetToken()==TokenNames::subtract) stk.push(kernel_.subtract(left,right));
            else if(i.GetToken()==TokenNames::multiply) stk.push(kernel_.multiply(left,right));
            else if(i.GetToken()==TokenNames::divide) stk.push(kernel_.divide(left,right));
            else if(i.GetToken()==TokenNames::pow) stk.push(kernel_.pow(left,right));
        }
        else if(i.GetType()==Token::UNARYOPERATOR)
        {
            CInstructionIndex o=stk.top();
            stk.pop();
            stk.push(kernel_.multiply(o, kernel_.constant(-1.0)));
        }
        else if(i.GetType()==Token::FUNCTION)
        {
            buildFunction(i.GetToken(), stk);
        }
        else if(i.GetType()==Token::VAR)
        {
            buildVar(i.GetToken(), stk);
        }
    }

    return stk.top();
}

CInstructionIndex CExpressionBuilder::evalAndStore(const std::string &expr)
{
    auto e=eval(expr);

    index_.push_back(e);

    return e;
}

CInstructionIndex CExpressionBuilder::evalAndStoreVar(const std::string &varname, const std::string &expr)
{
    auto e=eval(expr);
    insert_or_assign(storedvars_, varname, e);

    return e;
}

void CExpressionBuilder::store(CInstructionIndex i)
{
    index_.push_back(i);
}

CInstructionIndex CExpressionBuilder::retrieveVar(const std::string &varname)
{
    auto i=storedvars_.find(varname);
    if(i!=storedvars_.end()) return (*i).second;
    else return kernel_.zero();
}

void CExpressionBuilder::storeVar(const std::string &varname, CInstructionIndex i)
{
    insert_or_assign(storedvars_, varname, i);
}

void CExpressionBuilder::buildVar(const std::string &token, std::stack<CInstructionIndex> &stk)
{
    if(token==TokenNames::rand)
    {
        stk.push(kernel_.seed(prng_.get()));
    }
    else if (token==TokenNames::rand01)
    {
        stk.push(kernel_.constant(prng_.get01()));
    }
    else if (token==TokenNames::x)
    {
        stk.push(kernel_.x());
    }
    else if (token==TokenNames::y)
    {
        stk.push(kernel_.y());
    }
    else if (token==TokenNames::z)
    {
        stk.push(kernel_.z());
    }
    else if (token==TokenNames::w)
    {
        stk.push(kernel_.w());
    }
    else if (token==TokenNames::u)
    {
        stk.push(kernel_.u());
    }
    else if (token==TokenNames::v)
    {
        stk.push(kernel_.v());
    }
    else if (token==TokenNames::radial)
    {
        stk.push(kernel_.radial());
    }
    else
    {
        // Not a pre-built token, let's search the list of stored vars
        auto i=storedvars_.find(token);
        if(i!=storedvars_.end())
        {
            stk.push((*i).second);
        }
        else
        {
            stk.push(kernel_.getVar(token));
        }
    }
}

void CExpressionBuilder::buildFunction(const std::string &token, std::stack<CInstructionIndex> &stk)
{
    if(token==TokenNames::valueBasis)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.valueBasis(left,right));
    }
    else if(token==TokenNames::gradientBasis)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.gradientBasis(left,right));
    }
    else if(token==TokenNames::simplexBasis)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.simplexBasis(o));
    }
    else if(token==TokenNames::cellularBasis)
    {
        CInstructionIndex c9=stk.top();
        stk.pop();
        CInstructionIndex c8=stk.top();
        stk.pop();
        CInstructionIndex c7=stk.top();
        stk.pop();
        CInstructionIndex c6=stk.top();
        stk.pop();
        CInstructionIndex c5=stk.top();
        stk.pop();
        CInstructionIndex c4=stk.top();
        stk.pop();
        CInstructionIndex c3=stk.top();
        stk.pop();
        CInstructionIndex c2=stk.top();
        stk.pop();
        CInstructionIndex c1=stk.top();
        stk.pop();
        CInstructionIndex c0=stk.top();
        stk.pop();
        stk.push(kernel_.cellularBasis(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9));
    }
    else if(token==TokenNames::max)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.maximum(left,right));
    }
    else if(token==TokenNames::min)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.minimum(left,right));
    }
    else if(token==TokenNames::abs)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.abs(o));
    }
    else if(token==TokenNames::bias)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.bias(left,right));
    }
    else if(token==TokenNames::gain)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.gain(left,right));
    }
    else if(token==TokenNames::scale)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleDomain(left, right));
    }
    else if(token==TokenNames::scaleX)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleX(left,right));
    }
    else if(token==TokenNames::scaleY)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleY(left,right));
    }
    else if(token==TokenNames::scaleZ)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleZ(left,right));
    }
    else if(token==TokenNames::scaleW)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleW(left,right));
    }
    else if(token==TokenNames::scaleU)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleU(left,right));
    }
    else if(token==TokenNames::scaleV)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.scaleV(left,right));
    }
    else if(token==TokenNames::translate)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateDomain(left,right));
    }
    else if(token==TokenNames::translateX)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateX(left,right));
    }
    else if(token==TokenNames::translateY)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateY(left,right));
    }
    else if(token==TokenNames::translateZ)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateZ(left,right));
    }
    else if(token==TokenNames::translateW)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateW(left,right));
    }
    else if(token==TokenNames::translateU)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateU(left,right));
    }
    else if(token==TokenNames::translateV)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.translateV(left,right));
    }
    else if(token==TokenNames::rotateDomain)
    {
        CInstructionIndex c4=stk.top();
        stk.pop();
        CInstructionIndex c3=stk.top();
        stk.pop();
        CInstructionIndex c2=stk.top();
        stk.pop();
        CInstructionIndex c1=stk.top();
        stk.pop();
        CInstructionIndex c0=stk.top();
        stk.pop();
        stk.push(kernel_.rotateDomain(c0,c1,c2,c3,c4));
    }
    else if(token==TokenNames::mix)
    {
        CInstructionIndex c2=stk.top();
        stk.pop();
        CInstructionIndex c1=stk.top();
        stk.pop();
        CInstructionIndex c0=stk.top();
        stk.pop();
        stk.push(kernel_.mix(c0,c1,c2));
    }
    else if(token==TokenNames::select)
    {
        CInstructionIndex c4=stk.top();
        stk.pop();
        CInstructionIndex c3=stk.top();
        stk.pop();
        CInstructionIndex c2=stk.top();
        stk.pop();
        CInstructionIndex c1=stk.top();
        stk.pop();
        CInstructionIndex c0=stk.top();
        stk.pop();
        stk.push(kernel_.select(c0,c1,c2,c3,c4));
    }
    else if(token==TokenNames::clamp)
    {
        CInstructionIndex c2=stk.top();
        stk.pop();
        CInstructionIndex c1=stk.top();
        stk.pop();
        CInstructionIndex c0=stk.top();
        stk.pop();
        stk.push(kernel_.clamp(c0,c1,c2));
    }
    else if(token==TokenNames::cos)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.cos(o));
    }
    else if(token==TokenNames::sin)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.sin(o));
    }
    else if(token==TokenNames::tan)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.tan(o));
    }
    else if(token==TokenNames::acos)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.acos(o));
    }
    else if(token==TokenNames::asin)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.asin(o));
    }
    else if(token==TokenNames::atan)
    {
        CInstructionIndex o=stk.top();
        stk.pop();
        stk.push(kernel_.atan(o));
    }
    else if(token==TokenNames::tiers)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.tiers(left,right));
    }
    else if(token==TokenNames::smoothTiers)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.smoothTiers(left,right));
    }
    else if(token==TokenNames::dx)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.dx(left,right));
    }
    else if(token==TokenNames::dy)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.dy(left,right));
    }
    else if(token==TokenNames::dz)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.dz(left,right));
    }
    else if(token==TokenNames::dw)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.dw(left,right));
    }
    else if(token==TokenNames::du)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.du(left,right));
    }
    else if(token==TokenNames::dv)
    {
        CInstructionIndex right=stk.top();
        stk.pop();
        CInstructionIndex left=stk.top();
        stk.pop();
        stk.push(kernel_.dv(left,right));
    }
    else if(token==TokenNames::color)
    {
        CInstructionIndex a=stk.top();
        stk.pop();
        CInstructionIndex b=stk.top();
        stk.pop();
        CInstructionIndex g=stk.top();
        stk.pop();
        CInstructionIndex r=stk.top();
        stk.pop();

        stk.push(kernel_.combineRGBA(r,g,b,a));
    }
    else if(token==TokenNames::sigmoid)
    {
        CInstructionIndex rmp=stk.top();
        stk.pop();
        CInstructionIndex cntr=stk.top();
        stk.pop();
        CInstructionIndex src=stk.top();
        stk.pop();

        stk.push(kernel_.sigmoid(src,cntr,rmp));
    }
	else if(token==TokenNames::randomize)
	{
		CInstructionIndex seed=stk.top();
		stk.pop();
		CInstructionIndex low=stk.top(); stk.pop();
		CInstructionIndex high=stk.top(); stk.pop();
		stk.push(kernel_.randomize(seed,low,high));
	}
	else if(token==TokenNames::step)
	{
		CInstructionIndex control=stk.top(); stk.pop();
		CInstructionIndex val=stk.top(); stk.pop();
		stk.push(kernel_.step(val,control));
	}
	else if(token==TokenNames::linearStep)
	{
		CInstructionIndex control=stk.top(); stk.pop();
		CInstructionIndex high=stk.top(); stk.pop();
		CInstructionIndex low=stk.top(); stk.pop();
		stk.push(kernel_.linearStep(low,high,control));
	}
	else if(token==TokenNames::smoothStep)
	{
		CInstructionIndex control=stk.top(); stk.pop();
		CInstructionIndex high=stk.top(); stk.pop();
		CInstructionIndex low=stk.top(); stk.pop();
		stk.push(kernel_.smoothStep(low,high,control));
	}
	else if(token==TokenNames::smootherStep)
	{
		CInstructionIndex control=stk.top(); stk.pop();
		CInstructionIndex high=stk.top(); stk.pop();
		CInstructionIndex low=stk.top(); stk.pop();
		stk.push(kernel_.smootherStep(low,high,control));
	}
	else if(token==TokenNames::curveSection)
	{
		CInstructionIndex control=stk.top(); stk.pop();
		CInstructionIndex v1=stk.top(); stk.pop();
		CInstructionIndex v0=stk.top(); stk.pop();
		CInstructionIndex t1=stk.top(); stk.pop();
		CInstructionIndex t0=stk.top(); stk.pop();
		CInstructionIndex lowv=stk.top(); stk.pop();
		stk.push(kernel_.curveSection(lowv,t0,t1,v0,v1,control));
	}
	else if(token==TokenNames::fractal)
	{
		CInstructionIndex freq=stk.top(); stk.pop();
		CInstructionIndex octaves=stk.top(); stk.pop();
		CInstructionIndex lac=stk.top(); stk.pop();
		CInstructionIndex pers=stk.top(); stk.pop();
		CInstructionIndex layer=stk.top(); stk.pop();
		CInstructionIndex seed=stk.top(); stk.pop();
		stk.push(kernel_.fractal(seed,layer,pers,lac,octaves,freq));
	}
    else if(token==TokenNames::index)
    {
        InstructionListType *il=kernel_.getKernel();
        CInstructionIndex i=stk.top();
        stk.pop();
        unsigned int id=i.index_;
        if(id >= il->size() || (*il)[id].opcode_!=OP_Constant)
        {
            // Parameter passed to index must be a number
            // TODO: Figure out how to convey error to user
            stk.push(kernel_.zero());
        }
        else
        {
            unsigned int ic=(unsigned int)(*il)[id].outfloat_;
            if(ic>=index_.size())
            {
                // Index out of range
                stk.push(kernel_.zero());
            }
            else
            {
                stk.push(index_[ic]);
            }
        }


    }
    else if(token==TokenNames::rindex)
    {
        // Reverse index
        InstructionListType *il=kernel_.getKernel();
        CInstructionIndex i=stk.top();
        stk.pop();
        unsigned int id=i.index_;
        if(id >= il->size() || (*il)[id].opcode_!=OP_Constant)
        {
            // Parameter passed to index must be a number
            // TODO: Figure out how to convey error to user
            stk.push(kernel_.zero());
        }
        else
        {
            unsigned int ic=(unsigned int)(*il)[id].outfloat_;
            if(ic>=index_.size())
            {
                // Index out of range
                stk.push(kernel_.zero());
            }
            else
            {
                stk.push(index_[(index_.size()-1)-ic]);
            }
        }


    }

}
};
