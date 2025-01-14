#include ".//session.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<CesiumSession,
        TfType::Bases< UsdTyped > >();
    
    // Register the usd prim typename as an alias under UsdSchemaBase. This
    // enables one to call
    // TfType::Find<UsdSchemaBase>().FindDerivedByName("CesiumSessionPrim")
    // to find TfType<CesiumSession>, which is how IsA queries are
    // answered.
    TfType::AddAlias<UsdSchemaBase, CesiumSession>("CesiumSessionPrim");
}

/* virtual */
CesiumSession::~CesiumSession()
{
}

/* static */
CesiumSession
CesiumSession::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return CesiumSession();
    }
    return CesiumSession(stage->GetPrimAtPath(path));
}

/* static */
CesiumSession
CesiumSession::Define(
    const UsdStagePtr &stage, const SdfPath &path)
{
    static TfToken usdPrimTypeName("CesiumSessionPrim");
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return CesiumSession();
    }
    return CesiumSession(
        stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind CesiumSession::_GetSchemaKind() const
{
    return CesiumSession::schemaKind;
}

/* static */
const TfType &
CesiumSession::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<CesiumSession>();
    return tfType;
}

/* static */
bool 
CesiumSession::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
CesiumSession::_GetTfType() const
{
    return _GetStaticTfType();
}

UsdAttribute
CesiumSession::GetEcefToUsdTransformAttr() const
{
    return GetPrim().GetAttribute(CesiumTokens->cesiumEcefToUsdTransform);
}

UsdAttribute
CesiumSession::CreateEcefToUsdTransformAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(CesiumTokens->cesiumEcefToUsdTransform,
                       SdfValueTypeNames->Matrix4d,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

namespace {
static inline TfTokenVector
_ConcatenateAttributeNames(const TfTokenVector& left,const TfTokenVector& right)
{
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
}

/*static*/
const TfTokenVector&
CesiumSession::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        CesiumTokens->cesiumEcefToUsdTransform,
    };
    static TfTokenVector allNames =
        _ConcatenateAttributeNames(
            UsdTyped::GetSchemaAttributeNames(true),
            localNames);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--
