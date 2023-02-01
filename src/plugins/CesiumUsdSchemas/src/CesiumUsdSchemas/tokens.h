#ifndef CESIUM_TOKENS_H
#define CESIUM_TOKENS_H

/// \file cesium/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
// 
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "pxr/pxr.h"
#include ".//api.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/token.h"
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE


/// \class CesiumTokensType
///
/// \link CesiumTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// CesiumTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use CesiumTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(CesiumTokens->assetId);
/// \endcode
struct CesiumTokensType {
    CESIUM_API CesiumTokensType();
    /// \brief "assetId"
    /// 
    /// CesiumTilesetAPI
    const TfToken assetId;
    /// \brief "assetUrl"
    /// 
    /// CesiumTilesetAPI
    const TfToken assetUrl;
    /// \brief "ionToken"
    /// 
    /// CesiumData
    const TfToken ionToken;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var CesiumTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa CesiumTokensType
extern CESIUM_API TfStaticData<CesiumTokensType> CesiumTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif