import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { HelloComponent } from './hello.component';
import { DailyTrendComponent } from './daily-trend/daily-trend.component';
import { MonthlyTrendComponent } from './monthly-trend/monthly-trend.component';
import { HomePageComponent } from './home-page/home-page.component';

@NgModule({
  imports:      [ BrowserModule, FormsModule ],
  declarations: [ AppComponent, HelloComponent, DailyTrendComponent, MonthlyTrendComponent, HomePageComponent ],
  bootstrap:    [ AppComponent ]
})
export class AppModule { }
