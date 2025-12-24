#pragma once

/**
 * Dynamic Features Registry
 * Supports infinite modular customizable features
 */

#include <string>
#include <vector>
#include <functional>
#include <cstring>

struct Feature {
    const char* id;
    const char* label;
    const char* description;
    bool* toggle_ptr;  // Pointer to config field
    std::function<void()> on_toggle;  // Custom toggle callback
};

class FeaturesRegistry {
private:
    std::vector<Feature> features;
    
public:
    FeaturesRegistry() = default;
    
    // Register a new feature
    void registerFeature(const Feature& feature) {
        features.push_back(feature);
    }
    
    // Get all features
    const std::vector<Feature>& getFeatures() const {
        return features;
    }
    
    // Get feature by ID
    Feature* getFeatureById(const char* id) {
        for (auto& f : features) {
            if (strcmp(f.id, id) == 0) {
                return &f;
            }
        }
        return nullptr;
    }
    
    // Toggle feature by ID
    bool toggleFeature(const char* id) {
        auto* feature = getFeatureById(id);
        if (feature && feature->toggle_ptr) {
            *feature->toggle_ptr = !(*feature->toggle_ptr);
            if (feature->on_toggle) {
                feature->on_toggle();
            }
            return true;
        }
        return false;
    }
    
    // Get feature status
    bool getFeatureStatus(const char* id) const {
        for (const auto& f : features) {
            if (strcmp(f.id, id) == 0 && f.toggle_ptr) {
                return *f.toggle_ptr;
            }
        }
        return false;
    }
    
    // Get feature count
    size_t getFeatureCount() const {
        return features.size();
    }
};

// Global registry
extern FeaturesRegistry features_registry;
