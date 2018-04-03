#include "glslsyntax.h"

GLSLSyntax::GLSLSyntax(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
	keywordFormat.setForeground(Qt::darkBlue);	// color of text to be highlighted
	keywordFormat.setFontWeight(QFont::Bold);	// font weight of text to be highlighted
	QStringList keywordPatterns;
	keywordPatterns << "\\battribute\\b" << "\\bconst\\b" << "\\buniform\\b"
					<< "\\bvarying\\b" << "\\blayout\\b" << "\\bcentroid\\b"
					<< "\\bflat\\b" << "\\bsmooth\\b" << "\\bnoperspective\\b"
					<< "\\bcontinue\\b" << "\\bbreak\\b" << "\\bdo\\b"
					<< "\\bfor\\b" << "\\bwhile\\b" << "\\bswitch\\b"
					<< "\\bcase\\b" << "\\bdefault\\b" << "\\bif\\b"
					<< "\\belse\\b" << "\\bin\\b" << "\\bout\\b"
					<< "\\binout\\b" << "\\bfloat\\b" << "\\bint\\b"
					<< "\\bvoid\\b" << "\\bbool\\b" << "\\btrue\\b"
					<< "\\bfalse\\b" << "\\binvariant\\b" << "\\bdiscard\\b"
					<< "\\breturn\\b" << "\\bmat2\\b" << "\\bmat3\\b"
					<< "\\bmat4\\b" << "\\bmat2x2\\b" << "\\bmat3x3\\b"
					<< "\\bmat4x4\\b" << "\\bmat2x3\\b" << "\\bmat2x4\\b"
					<< "\\bmat3x2\\b" << "\\bmat3x4\\b" << "\\bmat4x2\\b"
					<< "\\bmat4x3\\b" << "\\bvec2\\b" << "\\bvec3\\b"
					<< "\\bvec4\\b" << "\\bivec2\\b" << "\\bivec3\\b"
					<< "\\bivec4\\b" << "\\bbvec2\\b" << "\\bbvec3\\b"
					<< "\\bbvec4\\b" << "\\buint\\b" << "\\buvec2\\b"
					<< "\\buvec3\\b" << "\\buvec4\\b" << "\\blowp\\b"
					<< "\\bmediump\\b" << "\\bhighp\\b" << "\\bprecision\\b"
					<< "\\bsampler1D\\b" << "\\bsampler2D\\b" << "\\bsampler3D\\b"
					<< "\\bsamplerCube\\b" << "\\bsampler1DShadow\\b" << "\\bsampler2DShadow\\b"
					<< "\\bsamplerCubeShadow\\b" << "\\bsampler1DArray\\b" << "\\bsampler2DArray\\b"
					<< "\\bsampler1DArrayShadow\\b" << "\\bsampler2DArrayShadow\\b"
					<< "\\bisampler1D\\b" << "\\bisampler2D\\b" << "\\bisampler3D\\b"
					<< "\\bisamplerCube\\b" << "\\bisampler1DArray\\b" << "\\bisampler2DArray\\b"
					<< "\\busampler1D\\b" << "\\busampler2D\\b" << "\\busampler3D\\b"
					<< "\\busamplerCube\\b" << "\\busampler1DArray\\b" << "\\busampler2DArray\\b"
					<< "\\bsampler2DRect\\b" << "\\bsampler2DRectShadow\\b" << "\\bisampler2DRect\\b"
					<< "\\busampler2DRect\\b" << "\\bsamplerBuffer\\b" << "\\bisamplerBuffer\\b"
					<< "\\busamplerBuffer\\b" << "\\bsampler2DMS\\b" << "\\bisampler2DMS\\b"
					<< "\\busampler2DMS\\b" << "\\bsampler2DMSArray\\b" << "\\bisampler2DMSArray\\b"
					<< "\\busampler2DMSArray\\b" << "\\bstruct\\b";
	// list of keywords to be highlighted and the way in which to highlight them (bold in this case)

	// rinse and repeat:
	functionFormat.setForeground(Qt::darkMagenta);
	functionFormat.setFontWeight(QFont::Bold);
	QStringList functionPatterns;
	functionPatterns << "\\bradians\\b" << "\\bdegrees\\b" << "\\bsin\\b"
					 << "\\bcos\\b" << "\\btan\\b" << "\\basin\\b"
					 << "\\bacos\\b" << "\\batan\\b" << "\\bsinh\\b"
					 << "\\bcosh\\b" << "\\btanh\\b" << "\\basinh\\b"
					 << "\\bacosh\\b" << "\\batanh\\b" << "\\bpow\\b"
					 << "\\bexp\\b" << "\\blog\\b" << "\\bexp2\\b"
					 << "\\blog2\\b" << "\\bsqrt\\b" << "\\binversesqrt\\b"
					 << "\\babs\\b" << "\\bsign\\b" << "\\bfloor\\b"
					 << "\\btrunc\\b" << "\\bround\\b" << "\\broundEven\\b"
					 << "\\bceil\\b" << "\\bfract\\b" << "\\bmod\\b"
					 << "\\bmodf\\b" << "\\bmin\\b" << "\\bmax\\b"
					 << "\\bclamp\\b" << "\\bmix\\b" << "\\bstep\\b"
					 << "\\bsmoothstep\\b" << "\\bisnan\\b" << "\\bisinf\\b"
					 << "\\bfloatBitsToInt\\b" << "\\bfloatBitsToUint\\b" << "\\bintBitsToFloat\\b"
					 << "\\buintBitsToFloat\\b" << "\\blength\\b" << "\\bdistance\\b"
					 << "\\bdot\\b" << "\\bcross\\b" << "\\bnormalize\\b"
					 << "\\bftransform\\b" << "\\bfaceforward\\b" << "\\breflect\\b"
					 << "\\brefract\\b" << "\\bmatrixCompMult\\b" << "\\bouterProduct\\b"
					 << "\\btranspose\\b" << "\\bdeterminant\\b" << "\\binverse\\b"
					 << "\\blessThan\\b" << "\\blessThanEqual\\b" << "\\bgreaterThan\\b"
					 << "\\bgreaterThanEqual\\b" << "\\bequal\\b" << "\\bnotEqual\\b"
					 << "\\bany\\b" << "\\ball\\b" << "\\bnot\\b"
					 << "\\btextureSize\\b" << "\\btexture\\b" << "\\btextureProj\\b"
					 << "\\btextureLod\\b" << "\\btextureOffset\\b" << "\\btexelFetch\\b"
					 << "\\btexelFetchOffset\\b" << "\\btextureProjOffset\\b" << "\\btextureLodOffset\\b"
					 << "\\btextureProjLod\\b" << "\\btextureProjLodOffset\\b" << "\\btextureGrad\\b"
					 << "\\btextureGradOffset\\b" << "\\btextureProjGrad\\b" << "\\btextureProjGradOffset\\b"
					 << "\\btexture1D\\b" << "\\btexture1DLod\\b" << "\\btexture1DProj\\b"
					 << "\\btexture1DProjLod\\b" << "\\btexture2D\\b" << "\\btexture2DLod\\b"
					 << "\\btexture2DProj\\b" << "\\btexture2DProjLod\\b" << "\\btexture3D\\b"
					 << "\\btexture3DLod\\b" << "\\btexture3DProj\\b" << "\\btexture3DProjLod\\b"
					 << "\\btextureCube\\b" << "\\btextureCubeLod\\b"
					 << "\\bshadow1D\\b" << "\\bshadow1DLod\\b" << "\\bshadow1DProj\\b"
					 << "\\bshadow1DProjLod\\b" << "\\bshadow2D\\b" << "\\bshadow2DLod\\b"
					 << "\\bshadow2DProj\\b" << "\\bshadow2DProjLod\\b" << "\\bdFdx\\b"
					 << "\\bdFdy\\b" << "\\bfwidth\\b" << "\\bnoise1\\b"
					 << "\\bnoise2\\b"<< "\\bnoise3\\b" << "\\bnoise4\\b";

	foreach(const QString &pattern, keywordPatterns)
	{
		Rule tempRule;
		tempRule.wordFormat = keywordFormat;	// make format for highlighting
		tempRule.regexp = QRegularExpression(pattern);	// make regular expressions from list above
		keywordRules.append(tempRule);	// add rule to the vector of rules
	}

	foreach(const QString &pattern, functionPatterns)
	{
		Rule tempRule;
		tempRule.wordFormat = functionFormat;
		tempRule.regexp = QRegularExpression(pattern);
		functionRules.append(tempRule);
	}
}

void GLSLSyntax::highlightBlock(const QString &text)
{
	foreach (const Rule &rule, keywordRules)
	{
		QRegularExpressionMatchIterator matchIterator = rule.regexp.globalMatch(text);
		// set regular expression to look for in text

		while (matchIterator.hasNext())	// browse through the document
		{
			QRegularExpressionMatch match = matchIterator.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.wordFormat);
			// set formatting if regular expression is found
		}
	}

	foreach (const Rule &rule, functionRules)
	{
		QRegularExpressionMatchIterator matchIterator = rule.regexp.globalMatch(text);
		while (matchIterator.hasNext())
		{
			QRegularExpressionMatch match = matchIterator.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.wordFormat);
		}
	}
}
