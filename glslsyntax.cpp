#include "glslsyntax.h"

GLSLSyntax::GLSLSyntax(QWidget *parent) : QSyntaxHighlighter(parent)
{
	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
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
}
