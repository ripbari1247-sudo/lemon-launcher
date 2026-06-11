        if (state.showMainMenu) {
            const float left = frame.left + 36.0f;
            const float menuRight = frame.left + (frame.right - frame.left) * 0.34f;
            const float previewLeft = menuRight + 34.0f;
            const float previewRight = frame.right - 36.0f;
            const float top = frame.top + 34.0f;
            const float buttonH = 62.0f;
            const float buttonGap = 24.0f;
            
            // Define labels - added "Play Offline" if not already logged in online
            const wchar_t* labels[] = { L"Play", L"Mods", L"Remote Files", L"Repair downloads", L"Sign out" };
            const wchar_t* menuIcons[] = { L"\uE768", L"\uE74C", L"\uE838", L"\uE72C", L"\uE7E8" };
            
            // Draw Title
            DrawText(title.c_str(), titleFormat_.Get(), D2D1::RectF(left, top, menuRight, top + 48.0f), white.Get());

            // Draw Standard Menu Items
            for (int i = 0; i < 5; ++i) {
                const float y = top + 76.0f + i * (buttonH + buttonGap);
                const D2D1_RECT_F button = D2D1::RectF(left, y, menuRight, y + buttonH);
                const bool sel = i == state.selectedMenuIndex;
                if (sel) GlowSelect(button, 14.0f);
                FillRound(button, sel ? accentSoft.Get() : surfaceFill.Get(), 14.0f);
                StrokeRound(button, sel ? accent.Get() : softEdge.Get(), 14.0f, sel ? 3.0f : 1.0f);
                DrawIcon(menuIcons[i], D2D1::RectF(button.left + 16.0f, button.top, button.left + 50.0f, button.bottom), sel ? accent.Get() : white.Get());
                const D2D1_RECT_F textRect = D2D1::RectF(button.left + 56.0f, button.top, button.right - 12.0f, button.bottom);
                DrawText(labels[i], bodyMid_.Get(), textRect, sel ? accent.Get() : white.Get());
            }

            // Draw "Play Offline" Button below standard menu
            const float offlineY = top + 76.0f + 5 * (buttonH + buttonGap);
            const D2D1_RECT_F offlineBtn = D2D1::RectF(left, offlineY, menuRight, offlineY + buttonH);
            const bool offlineSel = state.selectedMenuIndex == 6; // Index 6 for Offline
            if (offlineSel) GlowSelect(offlineBtn, 14.0f);
            FillRound(offlineBtn, surfaceFill.Get(), 14.0f);
            StrokeRound(offlineBtn, muted.Get(), 14.0f, offlineSel ? 3.0f : 1.0f);
            DrawIcon(L"\uE7FE", D2D1::RectF(offlineBtn.left + 16.0f, offlineBtn.top, offlineBtn.left + 50.0f, offlineBtn.bottom), muted.Get());
            DrawText(L"Play Offline", bodyMid_.Get(), D2D1::RectF(offlineBtn.left + 56.0f, offlineBtn.top, offlineBtn.right - 12.0f, offlineBtn.bottom), muted.Get());

            if (!state.status.empty()) {
                const D2D1_RECT_F statusRect = D2D1::RectF(left, frame.bottom - 88.0f, menuRight, frame.bottom - 28.0f);
                DrawText(state.status.c_str(), smallFormat_.Get(), statusRect, state.isError ? danger.Get() : muted.Get());
            }

            const D2D1_RECT_F preview = D2D1::RectF(previewLeft, top, previewRight, frame.bottom - 34.0f);
            FillRound(preview, black.Get(), 16.0f);
            StrokeRound(preview, softEdge.Get(), 16.0f, 1.0f);
            const float inset = 8.0f;
            const D2D1_RECT_F pano = D2D1::RectF(preview.left + inset, preview.top + inset, preview.right - inset, preview.bottom - inset);
            DrawScreenshots(pano);

            if (!state.detail.empty()) {
                const D2D1_RECT_F detailRect = D2D1::RectF(preview.left + 26.0f, preview.bottom - 82.0f, preview.right - 26.0f, preview.bottom - 24.0f);
                DrawText(state.detail.c_str(), smallFormat_.Get(), detailRect, muted.Get());
            }

            finishDraw();
            return;
        }