/*
  ==============================================================================

    helpers.cpp
    Created: 21 Dec 2024 8:38:20pm
    Author:  Kimi Weng

  ==============================================================================
*/

#include "helpers.h"
#include "JuceHeader.h"

auto streamToVector (juce::InputStream& stream) {
    using namespace juce;
    std::vector<std::byte> result ((size_t) stream.getTotalLength());
    stream.setPosition (0);
    [[maybe_unused]] const auto bytesRead = stream.read (result.data(), result.size());
    jassert (bytesRead == (ssize_t) result.size());
    return result;
}

const char* getMimeForExtension (const juce::String& extension) {
    using namespace juce;
    static const std::unordered_map<juce::String, const char*> mimeMap =
    {
        { { "htm"   },  "text/html"                },
        { { "html"  },  "text/html"                },
        { { "txt"   },  "text/plain"               },
        { { "jpg"   },  "image/jpeg"               },
        { { "jpeg"  },  "image/jpeg"               },
        { { "svg"   },  "image/svg+xml"            },
        { { "ico"   },  "image/vnd.microsoft.icon" },
        { { "json"  },  "application/json"         },
        { { "png"   },  "image/png"                },
        { { "css"   },  "text/css"                 },
        { { "map"   },  "application/json"         },
        { { "js"    },  "text/javascript"          },
        { { "woff2" },  "font/woff2"               }
    };

    if (const auto it = mimeMap.find (extension.toLowerCase()); it != mimeMap.end())
        return it->second;

    jassertfalse;
    return "";
}

std::optional<Resource> getResource(const juce::String& url) {
    static const auto resourceFileRoot = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("Frontend/build");
//    static const auto resourceFileRoot = juce::File("/Users/pieface3450/Dropbox/coding_projects/c++/KSIO/Frontend/build");
    const auto resourceToRetreive = url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);
    const auto resource = resourceFileRoot.getChildFile(resourceToRetreive).createInputStream();
    if (resource) {
        const auto extension = resourceToRetreive.fromLastOccurrenceOf(".", false, false);
        return juce::WebBrowserComponent::Resource{streamToVector(*resource), getMimeForExtension(extension)};
    }
    return std::nullopt;
}
